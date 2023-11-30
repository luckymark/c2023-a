import torch
from torch import nn


class GobangCNN(nn.Module):
    def __init__(self):
        super(GobangCNN, self).__init__()
        self.publicConv = torch.nn.Sequential(
            torch.nn.Conv2d(in_channels=17, out_channels=32, kernel_size=(3, 3), padding=1, stride=1),
            torch.nn.BatchNorm2d(32),
            torch.nn.ReLU(),
            torch.nn.Conv2d(in_channels=32, out_channels=64, kernel_size=(3, 3), padding=1, stride=1),
            torch.nn.BatchNorm2d(64),
            torch.nn.ReLU(),
            torch.nn.Conv2d(in_channels=64, out_channels=128, kernel_size=(3, 3), padding=1, stride=1),
            torch.nn.BatchNorm2d(128),
            torch.nn.ReLU()
        )
        self.value = torch.nn.Sequential(
            torch.nn.Conv2d(in_channels=128, out_channels=2, kernel_size=(1, 1), padding=0, stride=1),
            torch.nn.BatchNorm2d(2),
            torch.nn.ReLU(),
            torch.nn.Flatten(),
            torch.nn.Linear(2 * 15 * 15, 64),
            torch.nn.ReLU(),
            torch.nn.Linear(64, 15 * 15),
            torch.nn.Tanh(),
            torch.nn.Unflatten(1, (15, 15))
        )
        self.policy = torch.nn.Sequential(
            torch.nn.Conv2d(in_channels=128, out_channels=4, kernel_size=(1, 1), padding=0, stride=1),
            torch.nn.BatchNorm2d(4),
            torch.nn.ReLU(),
            torch.nn.Flatten(),
            torch.nn.Linear(4 * 15 * 15, 15 * 15),
            torch.nn.Softmax(),
            torch.nn.Unflatten(1, (15, 15))
        )

    def forward(self, x):
        y = self.publicConv(x)
        v = self.value(y)
        p = self.policy(y)
        return v, p


class ValuePolicyLoss(nn.Module):
    def __init__(self, model, p_cnn, v_cnn, p_mcts, v_mcts, lambda_reg=0.01):
        super(ValuePolicyLoss, self).__init__()
        self.model = model
        self.p_cnn = p_cnn
        self.v_cnn = v_cnn
        self.p_mcts = p_mcts
        self.v_mcts = v_mcts
        self.lambda_reg = lambda_reg

    def forward(self):
        l2_reg = None
        for param in self.model.parameters():
            if l2_reg is None:
                l2_reg = param.norm(2)
            else:
                l2_reg = l2_reg + param.norm(2)
        p_cnn_tensor = torch.Tensor(self.p_cnn)
        p_mcts_tensor = torch.Tensor(self.p_mcts)
        v_cnn_tensor = torch.Tensor(self.v_cnn)
        v_mcts_tensor = torch.Tensor(self.v_mcts)
        loss = torch.norm(v_mcts_tensor - v_cnn_tensor, 2) ** 2 - torch.dot(p_mcts_tensor,
                                                                            torch.log(
                                                                                p_cnn_tensor)) + self.lambda_reg * l2_reg
        return loss


class CNNRun:
    def __init__(self, model_name: str = None, opt_name: str = None):
        default_device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.model = GobangCNN().to(device=default_device)
        if model_name is not None:
            self.model.load_state_dict(torch.load(model_name + '.pth', map_location=default_device))
        self.optimizer = torch.optim.Adam(self.model.parameters())
        if opt_name is not None:
            self.optimizer.load_state_dict(torch.load(opt_name + '.pth'))
        self.loss = ValuePolicyLoss

    def forward_propagation(self, input_data):
        input_tensor = torch.tensor(input_data)
        # ???输出方式待定
        self.model(input_tensor)

    def backward_propagation(self, p_cnn, p_mcts, v_cnn, v_mcts):
        loss = self.loss(self.model, p_cnn, p_mcts, v_cnn, v_mcts)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()
