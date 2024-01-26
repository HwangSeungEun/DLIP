def calculate_similarity(file1_path, file2_path):
    with open(file1_path, 'r') as file1, open(file2_path, 'r') as file2:
        text1 = file1.read()
        text2 = file2.read()

    # 두 텍스트의 길이 계산
    len_text1 = len(text1)
    len_text2 = len(text2)

    # 최소 길이 계산
    min_len = min(len_text1, len_text2)

    # 위치별로 일치하는 숫자 개수 계산
    num_same = sum(1 for a, b in zip(text1, text2) if a == b)

    # 백분율로 일치율 계산
    similarity = (num_same / min_len) * 100

    return similarity

# 텍스트 파일 경로 설정
file1_path = 'C:\\Users\erich\source\\repos\DLIP\LAB\DLIP_LAB4_21800805_Hwangseungeun\LAB_Parking_counting_result_answer_student_modified.txt'
file2_path = 'C:\\Users\erich\source\\repos\DLIP\LAB\DLIP_LAB4_21800805_Hwangseungeun\제출 임시 파일\counting_result.txt'

# 일치율 계산
similarity = calculate_similarity(file1_path, file2_path)

print(f"accuracy: {similarity:.2f}%")

# accuracy: 81.29%