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


if __name__ == "__main__":
    if len(sys.argv) > 0:
        print(sys.argv[1])
        print(sys.argv[2])
    else:
        print("need input file")
        exit()

    interval_seq = list()
    with open(sys.argv[1], "r") as f:
        for line in f:
            temp_s, temp_e = line.split()
            temp_s = int(temp_s)
            temp_e = int(temp_e)
            interval_seq.append(interval(temp_s, temp_e))

    index = list(range(1, len(interval_seq) + 1))
    start = [i.s() for i in interval_seq]
    end = [i.e() for i in interval_seq]
    length = [i.l() for i in interval_seq]

    print(len(start))
    # print(start)
    # start = np.array([10, 30, 50, 20, 33])
    # end = np.array([31, 61, 95, 55, 110])
    # 計算長度
    # h = list()
    # for i in range(len(start)):
    #     h.append(end[i]-start[i] - 1)
    # height = np.array(h)

    subseq = list()
    with open(sys.argv[2], "r") as f:
        temp = f.readline()
        subseq = [int(i) + 1 for i in filter(None, temp.rstrip('\n').split(', '))]
    print(subseq)

    date = list()
    with open(sys.argv[3], "r") as f:
        date = [i.rstrip() for i in f]
    # print(date)


    color_list = list()
    for i in range(1, len(index)+1):
        if i in subseq:
            color_list.append('#FE7A7B')
        else:
            color_list.append('#66CCCC')

    # c_list = ['#FE7A7B', '#FF9966', '#FFCC66', '#99D8B9', '#66CCCC']  #色票
    # labels = ['X1', 'X2', 'X3', 'X4', 'X5']

    plt.figure(figsize=(20,10))
    plt.ylim(420, 600)
    plt.ylabel('The lowet and highest stock price', fontweight='bold', fontsize=15)
    plt.xlabel('Date', fontweight='bold', fontsize=15)
    plt.xticks(index, date, rotation='vertical', fontsize=8)
    plt.bar(index, length, bottom=start, color=color_list, 
                width=1.0, edgecolor='black', linewidth = 1)
    plt.subplots_adjust(top=0.99, bottom=0.1, right=0.995, left=0.04)
    plt.margins(0, 0)
    plt.savefig('test.svg')

    plt.show()
