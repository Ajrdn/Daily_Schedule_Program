#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct schedule {
	char *Todo;
	char *AP;
	int time, time1, time2;
	struct schedule *next;
}schedule;

typedef struct {
	schedule * head;
}scheduleHead;

scheduleHead *CreateScheduleHead();
void PrintMenu(int number);
void InsertSchedule(scheduleHead *schedulehead);
void DeleteSchedule(scheduleHead *schedulehead);
void PrintSchedule(scheduleHead *schedulehead);
void SearchSchedule(scheduleHead *schedulehead);

int main(){
  int numder;
	scheduleHead *schedulehead = CreateScheduleHead();

  while(1) {
		PrintMenu(1);
    scanf("%d", &numder);
		printf("\n");

    switch(numder) {
      case 1 : InsertSchedule(schedulehead);
      break;

      case 2 : DeleteSchedule(schedulehead);
			break;

      case 3 : PrintSchedule(schedulehead);
      break;

			case 4 : SearchSchedule(schedulehead);
			break;

			case 5 : printf("프로그램을 종료합니다.\n");
			return 0;
			break;

			default : printf("숫자를 다시 입력해 주세요.\n");
    }
  }
	return 0;
}

scheduleHead *CreateScheduleHead() {

	scheduleHead *schedulehead;
	schedulehead = (scheduleHead*)malloc(sizeof(scheduleHead));
	schedulehead -> head = NULL;
	return schedulehead;

}

void PrintMenu(int number) {

	switch(number) {
		case 1 : printf("다음 중 하고자 하시는 작업을 선택해 주세요.\n");
		printf("+--------------------+\n");
		printf("| 일정 추가      (1) |\n");
  	printf("| 일정 삭제      (2) |\n");
  	printf("| 일정 출력      (3) |\n");
		printf("| 일정 찾기      (4) |\n");
  	printf("| 프로그램 종료  (5) |\n");
		printf("+--------------------+\n");
		break;

		case 2 : printf("다음 중 출력하고자 하시는 일정을 선택해 주세요.\n");
		printf("+--------------------+\n");
		printf("| 오전 일정 출력 (1) |\n");
		printf("| 오후 일정 출력 (2) |\n");
		printf("| 모든 일정 출력 (3) |\n");
  	printf("+--------------------+\n");
		break;
	}

}

void InsertSchedule(scheduleHead *schedulehead) {

	int time, time1, time2;
	char *todo = (char *)malloc(sizeof(char) * 100);
	char *AP = (char *)malloc(sizeof(char) * 10);
	char *hour = (char *)malloc(sizeof(char) * 10);
	char *minute = (char *)malloc(sizeof(char) * 10);
	schedule *newSchedule;
	newSchedule = (schedule*)malloc(sizeof(schedule));
	
	while(1) {
		printf("시간을 입력해 주세요.(입력 양식 : 오전 / 오후 OO시 OO분)\n");
		scanf("%s %d%s %d%s", AP, &time1, hour, &time2, minute);
		printf("\n");

		if (strcmp(AP, "오전") == 0 && strcmp(hour, "시") == 0 && strcmp(minute, "분") == 0) {
			time = (time1 % 12) * 60 + time2;
			break;
		}

		else if (strcmp(AP, "오후") == 0 && strcmp(hour, "시") == 0 && strcmp(minute, "분") == 0) {
			time = (time1 % 12 + 12) * 60 + time2;
			break;
		}

		else {
			printf("다시 입력해 주세요.\n");
			printf("\n");
		}
	}

  printf("추가하실 일정을 입력해 주세요.\n");
	getchar();
  fgets(todo, 100, stdin);
	printf("\n");
	todo[strlen(todo) - 1] = '\0';

	newSchedule -> Todo = todo;
	newSchedule -> AP = AP;
	newSchedule -> time = time;
	newSchedule -> time1 = time1;
	newSchedule -> time2 = time2;
	newSchedule -> next = NULL;

	if (schedulehead -> head == NULL) {
		schedulehead -> head = newSchedule;
		printf("'%s' 일정이 추가되었습니다.\n", todo);
		printf("\n");
		return ;
	}

	else if (time < schedulehead -> head -> time) {
		newSchedule -> next = schedulehead -> head;
		schedulehead -> head = newSchedule;
		printf("'%s' 일정이 추가되었습니다.\n", todo);
		printf("\n");
		return ;
	}

	schedule *temp = schedulehead -> head;
	
	while(temp -> next != NULL) {
		if (time <= temp -> next -> time) {
			newSchedule -> next = temp -> next;
			temp -> next = newSchedule;
			printf("'%s' 일정이 추가되었습니다.\n", todo);
			printf("\n");
			return ;
		}
		temp = temp -> next;
	}
	temp -> next = newSchedule;
	printf("'%s' 일정이 추가되었습니다.\n", todo);
	printf("\n");

}

void DeleteSchedule(scheduleHead *schedulehead) {

	char *delete = (char *)malloc(sizeof(char) * 100);
	schedule *temp;

	printf("삭제하실 일정을 입력해 주세요.\n");
	getchar();
  fgets(delete, 100, stdin);
	delete[strlen(delete) - 1] = '\0';
	printf("\n");

	if (strcmp(schedulehead -> head -> Todo, delete) == 0) {
    temp = schedulehead -> head;
    schedulehead -> head = temp -> next;
    free(temp);
		printf("'%s' 일정이 삭제되었습니다.\n", delete);
		printf("\n");
    return ;
  }

	schedule *temp2, *temp3;
	temp = schedulehead -> head;
  temp2 = NULL;

	while (temp != NULL) {
		if (strcmp(temp -> Todo, delete) == 0) {
      temp3 = temp;
      temp2 -> next = temp -> next;
      free(temp3);
			printf("'%s' 일정이 삭제되었습니다.\n", delete);
			printf("\n");
      return ;
    }
    temp2 = temp;
    temp = temp -> next;
	}
  printf("찾으시는 일정 '%s'은/는 없습니다.\n", delete);
	printf("\n");
	return ;

}

void PrintSchedule(scheduleHead *schedulehead) {

	if (schedulehead -> head == NULL) {
		printf("등록된 일정이 없습니다.\n");
		printf("\n");
		return ;
	}
	
	schedule *temp;
	temp = schedulehead -> head;
	int number;

	while(1) {
		PrintMenu(2);
		scanf("%d", &number);
		printf("\n");

		if (number == 1) {
			if (strcmp(temp -> AP, "오전") != 0) {
				printf("등록된 오전 일정이 없습니다.\n");
				printf("\n");
				return ;
			}

			printf("+-------오전 일정---------------------------------------+\n");
		
			while (temp != NULL) {
				if (strcmp(temp -> AP, "오전") != 0) {
					printf("+-------------------------------------------------------+\n");
					printf("\n");
					return ;
				}

				if (temp -> time1 == 0) {
					printf("%d시 %d분 : %s\n", temp -> time1 + 12, temp -> time2, temp -> Todo);
					temp = temp -> next;
				}

				else {
					printf("%d시 %d분 : %s\n", temp -> time1, temp -> time2, temp -> Todo);
					temp = temp -> next;
				}
			}
			printf("+-------------------------------------------------------+\n");
			printf("\n");
			return ;
		}

		else if (number == 2) {
			while (temp -> next != NULL) {
				temp = temp -> next;
			}

			if (strcmp(temp -> AP, "오후") != 0) {
				printf("등록된 오후 일정이 없습니다.\n");
				printf("\n");
				return ;
			}

			temp = schedulehead -> head;

			printf("+-------오후 일정---------------------------------------+\n");

			while (temp != NULL) {
				if (strcmp(temp -> AP, "오후") != 0) {
					temp = temp -> next;
				}

				else {
					if (temp -> time1 == 0) {
						printf("%d시 %d분 : %s\n", temp -> time1 + 12, temp -> time2, temp -> Todo);
						temp = temp -> next;
					}
					
					else {
						printf("%d시 %d분 : %s\n", temp -> time1, temp -> time2, temp -> Todo);
						temp = temp -> next;
					}
				}
			}
			printf("+-------------------------------------------------------+\n");
			printf("\n");
			return ;
		}

		else if (number == 3) {
			printf("+-------하루 일정---------------------------------------+\n");
			while (temp != NULL) {
				printf("%s %d시 %d분 : %s\n", temp -> AP, temp -> time1, temp -> time2, temp -> Todo);
				temp = temp -> next;
			}
			printf("+-------------------------------------------------------+\n");
			printf("\n");
			return ;
		}

		else {
			printf("숫자를 다시 입력해 주세요.\n");
		}
	}

}

void SearchSchedule(scheduleHead *schedulehead) {

	char *search = (char *)malloc(sizeof(char) * 100);
	schedule *temp;
	temp = schedulehead -> head;

	printf("찾으시는 일정을 입력해 주세요.\n");
	getchar();
	fgets(search, 100, stdin);
	search[strlen(search) - 1] = '\0';
	printf("\n");

	while (temp != NULL) {
		if (strcmp(temp -> Todo, search) == 0) {
			printf("찾으시는 일정 '%s'의 시간은 %s %d시 %d분입니다.\n", temp -> Todo, temp -> AP, temp -> time1, temp -> time2);
			printf("\n");
			return ;
		}
		temp = temp -> next;
	}
	printf("찾으시는 일정 '%s'은/는 없습니다.\n", search);
	printf("\n");

}