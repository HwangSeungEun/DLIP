import torch
import torchvision
import torchvision.transforms as transforms
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import matplotlib.pyplot as plt


# Get cpu or gpu device for training.
device = "cuda" if torch.cuda.is_available() else "cpu"

print(f"Using {device} device")
if torch.cuda.is_available(): print(f'Device name: {torch.cuda.get_device_name(0)}') 


#########################################################
# [EXERCISE] Create VGG-16 architecture (refer to part1)
#########################################################
class VGG16(nn.Module):
    def __init__(self):
        super(VGG16, self).__init__()

        self.conv_layers = nn.Sequential(            
            # C1
            # (input ch, output ch, filter size)
            nn.Conv2d(3, 64, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(64, 64, 3, padding=1),
            nn.ReLU(),

            # S1
            # pooling size (2,2)
            nn.MaxPool2d(2,2),


            # C3
            nn.Conv2d(64, 128, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(128, 128, 3, padding=1),
            nn.ReLU(),

            # S2
            nn.MaxPool2d(2,2),

            # C5
            nn.Conv2d(128, 256, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(256, 256, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(256, 256, 3, padding=1),
            nn.ReLU(),

            # S3
            nn.MaxPool2d(2,2),

            # C7
            nn.Conv2d(256, 512, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding=1),
            nn.ReLU(),

            # S4
            nn.MaxPool2d(2,2),

            # C10
            nn.Conv2d(512, 512, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding=1),
            nn.ReLU(),
            nn.Conv2d(512, 512, 3, padding=1),
            nn.ReLU(),

            # S5
            nn.MaxPool2d(2,2)
        )

        self.flatten = nn.Flatten()

        self.fc_layers = nn.Sequential(
            # F5
            nn.Linear(512 * 7 * 7, 4096),
            nn.ReLU(),

            # F6
            nn.Linear(4096, 4096),
            nn.ReLU(),

            # OUTPUT
            nn.Linear(4096, 1000)
        )            


    def forward(self, x):
        x = self.conv_layers(x)
        # Converting multidimensional data to one dimension for FC operation
        x = self.flatten(x)
        logit = self.fc_layers(x)        
        return logit

model = VGG16().to(device)
print(model)

from torchsummary import summary
summary(model, (3, 224, 244))
