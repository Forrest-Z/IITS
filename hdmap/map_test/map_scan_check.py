import sys


class scanner(object):
    def __init__(self, module, target_words):
        self.module = '<'+module
        self.module_end = '</'+module.replace(' ', '')
        self.target_strings = ""
        self.target_words = target_words
        for target_word in target_words:
            if target_word == module:
                self.module_end = self.module
                self.target_words = [self.module]
            self.target_strings = self.target_strings + target_word + " "
        #print(self.module, self.module_end, self.target_strings)
        self.Inmodule = False
        self.module_line_num = 0
        self.toFind_target = False
        self.module_num = 0
        self.target_num = 0
        self.target_total = 0
        self.target_lines = []
        self.lane_ids = []

    def scan_file(self, lines):
        line_num = 0
        for line in lines:
            line_num = line_num+1
            if line.find(self.module) > -1:
                #print("find ",self.module)
                self.module_num = self.module_num + 1
                if self.Inmodule == False:
                    self.Inmodule = True
                    self.toFind_target = True
                    self.module_line_num = line_num
                else:
                    print(" no", self.module_end, ",", self.module, "_num: ",
                          self.module_line_num, '  line_num: ', line_num)
            for target_word in self.target_words:
                if line.find(target_word) > -1:
                    self.target_num = self.target_num + 1
                    self.target_lines.append(str(line_num) + "  "+line)
                    self.lane_ids.append('road: '+str(self.module_num)+' lanesegtion: '+str(
                        self.target_num) + " "+line.replace('  ', ''))
                    #print("find ",target_word)
                    self.toFind_target = False
            if line.find(self.module_end) > -1:

                self.target_total = self.target_total + self.target_num
                self.target_num = 0
                #print("find ",self.module_end)
                self.target_lines.append("  \n")
                if self.toFind_target == True:
                    self.toFind_target = False
                    print(" no ", self.target_strings, self.module, "_num: ",
                          self.module_line_num, '  line_num: ', line_num)
                if self.Inmodule == True:
                    self.Inmodule = False
                    self.module_line_num = line_num
        if self.target_total == 0:
            print(self.target_strings, "  lost  in ", self.module)
        # print(self.module, "_num: ", self.module_num,
        #       self.target_strings, "_num: ", self.target_total)

    def write_file(self):
        f = open(self.target_strings.replace(' ', '_')+'.txt', "w")
        for line in self.target_lines:
            f.write(line)
        f.close()

    def write_lanesegtion(self):
        f = open(self.target_strings.replace(
            ' ', '_')+'lane_setion'+'.txt', "w")
        for line in self.lane_ids:
            f.write(line)
        f.close()


# def file_scan(filename):
#     line_num = 0
#     find_link = False
#     link_num = 0
#     toFind_suor = False
#     file1 = open('./resource/1118/move_lane.xodr', 'rt')
#     lines = file1.readlines()
#     line_num = 0
#     for line in lines:
#         # print(line)
#         # if line_num < 200:
#         #print(line_num, "  ", line)
#         line_num = line_num+1
#         if line.find('<link>') > -1:
#             if find_link == False:
#                 find_link = True
#                 toFind_suor = True
#                 link_num = line_num
#             else:
#                 print(" no </link>, link_num: ",
#                       link_num, '  line_num: ', line_num)
#         if line.find('/link') > -1:
#             if toFind_suor == True:
#                 toFind_suor = False
#                 print(" no succesor or predecessor, link_num: ",
#                       link_num, '  line_num: ', line_num)
#             if find_link == True:
#                 find_link = False
#                 link_num = line_num
#         if line.find('predecessor') > -1 or line.find('successor') > -1:
#             toFind_suor = False
#     file1.close()
if __name__ == "__main__":
    # file_scan('test')
    file1 = open('./resource/move_lane_1120_elevation_fix.xodr', 'rt')
    lines = file1.readlines()
    link_scanner = scanner('link', ['predecessor', 'successor'])
    link_scanner.scan_file(lines)
    link_scanner.write_file()

    header_scanner = scanner('header', ['geoReference'])
    header_scanner.scan_file(lines)

    height_scanner = scanner('elevation', ['elevation'])
    height_scanner.scan_file(lines)

    lane_scanner = scanner('road ', ['laneSection'])
    lane_scanner.scan_file(lines)
    lane_scanner.write_lanesegtion()
    file1.close()
