import sys
import matplotlib.pyplot as plt


class interval:
    __s = 0
    __e = 0
    __l = 0

    def __init__(self, s, e) -> None:
        self.__s = s
        self.__e = e
        self.__l = e - s + 1

    def s(self) -> int:
        return self.__s

    def e(self) -> int:
        return self.__e

    def l(self) -> int:
        return self.__l


def createLabels(data):
    for index, item in enumerate(data):
        height = item.get_height()
        plt.text(
            item.get_x()+item.get_width()/2.,
            item.get_y()+height*1.05,
            '%d-%d' % (int(start[index]), int(end[index])),
            ha="center",
            va="bottom",
        )

# 20231_date.txt 20231_miis_full.txt  20231.txt
if __name__ == "__main__":
    if len(sys.argv) == 4:
        print(sys.argv[1]) # stock
        print(sys.argv[2]) # years
        print(sys.argv[3]) # algorithm
    else:
        print("need input file")
        exit()

    path = sys.argv[1] + "/" + sys.argv[2] + "/"

    interval_seq = list()
    with open(path + "seq.txt", "r") as f: # highest and lowet stock price
        for line in f:
            temp_s, temp_e = line.split()
            temp_s = int(temp_s)
            temp_e = int(temp_e)
            interval_seq.append(interval(temp_s, temp_e))

    index = list(range(1, len(interval_seq) + 1))
    start = [i.s() for i in interval_seq]
    end = [i.e() for i in interval_seq]
    length = [i.l() for i in interval_seq]

    date = list()
    with open(path + "date.txt", "r") as f: # date
        date = [i.rstrip() for i in f]

    subseq = list()
    with open(path + sys.argv[3] + ".txt", "r") as f: # index of the subsequence
        temp = f.readline()
        subseq = [int(i) + 1 for i in filter(None, temp.rstrip('\n').split(', '))]

    color_list = list()
    for i in range(1, len(index)+1):
        if i in subseq:
            color_list.append('#FE7A7B')
        else:
            color_list.append('#66CCCC')

    # c_list = ['#FE7A7B', '#FF9966', '#FFCC66', '#99D8B9', '#66CCCC']  #色票
    # labels = ['X1', 'X2', 'X3', 'X4', 'X5']

    plt.figure(figsize=(20,10))
    # plt.ylim(420, 600)
    plt.ylim(440, 690)
    plt.ylabel('The lowet and highest stock price', fontweight='bold', fontsize=15)
    plt.xlabel('Date', fontweight='bold', fontsize=15)
    plt.xticks(index, date, rotation='vertical', fontsize=8)
    plt.bar(index, length, bottom=start, color=color_list, 
                width=1.0, edgecolor='black', linewidth = 1)
    plt.subplots_adjust(top=0.99, bottom=0.1, right=0.995, left=0.04)
    plt.margins(0, 0)
    plt.savefig(sys.argv[2] + '_' + sys.argv[3] + '.eps')

    plt.show()
