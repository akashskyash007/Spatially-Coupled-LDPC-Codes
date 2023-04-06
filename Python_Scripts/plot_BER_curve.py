import matplotlib.pyplot as plt

def read_file():
    with open("/home/akash/MyFiles/SpatiallyCoupledLDPC/C_Scripts/LAYERED_DECODER_IMPLEMENTATION_VERY_SMALL_BLOCK_LENGTHS/BER_RESULTS.txt", "r") as f:
        line = f.read()
        numbers = line.split(" ")
        ber_values = []
        for i in range(100):
            ber_values.append(float(numbers[i]))
        return ber_values

def plot_ber_curve(ber_values):
    EbNodB = [i * 0.1 for i in range(100)]
    plt.figure(figsize = (15, 7))
    plt.plot(EbNodB, ber_values)
    plt.yscale("log")
    plt.xlabel("Eb/No (in dB)")
    plt.ylabel("Bit Error Rate")
    plt.xticks(range(10))
    plt.yticks([pow(10, -1 * i) for i in range(4)])
    plt.grid(which = 'both', linestyle = 'dashed')
    plt.title('BER v/s SNR plot')
    plt.savefig("BER_CURVE.png")
    plt.show()
    
if __name__ == "__main__":
    ber_values = read_file()
    plot_ber_curve(ber_values)
