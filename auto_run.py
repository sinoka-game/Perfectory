# gcc 명령어를 자동으로 생성합니다
# 초기버전 조건
# main.c에만 대응
# 모든 소스코드는 src에 있다고 가정
# 모든 include는 코드 중간에 있지 않다고 가정
# 스크립트는 src와 같은 폴더 내에 있다고 가정
# 작동방식: C언어 코드를 읽고 include 부분을 읽어서 자동생성

with open("src/main.c", "r") as file_read:
    file = file_read.read().split("\n")

libs = []

for line in file:
    if len(line) <= 0:
        break
    if line[0] == "#":
        if line[1:8] == "include":
            libs.append(line[10:-3])
        else: break
    else: break

print(libs)
