import sys
import random

def generate_noise(n, sigma):
    noise_vector = []
    for i in range(n):
        noise_vector.append(random.gauss(0, sigma))
    f = open("/home/akash/MyFiles/SpatiallyCoupledLDPC/C_Scripts/LAYERED_DECODER_IMPLEMENTATION/noise_vector.txt", "w");
    for i in range(n):
        f.write(str(noise_vector[i]) + "\n");
    f.close()

if __name__ == "__main__":
    n = int(sys.argv[1])
    sigma = float(sys.argv[2])
    generate_noise(n, sigma)
