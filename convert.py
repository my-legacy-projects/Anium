import sys

def convert(signture: str):
    old_sig = signture.split("\\x")

    for i in range(0, len(old_sig)):
        if old_sig[i] == "00":
            old_sig[i] = "?"

    sig = ""

    for i in range(1, len(old_sig)):
        sig += old_sig[i] + " "

    return sig[:-1]

if __name__ == "__main__":
    print(convert(sys.argv[1]))
