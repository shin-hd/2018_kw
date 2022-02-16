#include "Manager.h"

/*  ※ 과제 제출 시 본 주석 삭제
구현 편의성을 위해 일부 함수에 코드가 작성되어 있으며, 해당 코드는 이용 또는
삭제, 변경이 가능함. 또한, 일부 코드는 과제 요구사항에 맞게 변경이 필요할 수
있음 (예: 콘솔 출력 -> 파일 출력) ★ 단, 제공된 프로젝트 파일의 클래스, 멤버
변수, 멤버 함수의 이름과 형식은 변경 불가능 ★ 제공된 함수내의 코드를 그대로
이용할 경우, 핵심 코드에는 반드시 주석 추가
*/

int main(void) {
  cout.setf(ios::fixed);
  cout.precision(2);

  int bpOrder = 3;

  Manager ds(bpOrder);
  ds.run("command.txt");

  return 0;
}

bool compare(pair<pair<double, int>, StockData* > a, pair<pair<double, int>, StockData* > b) {
	/* 아래 작성된 코드는 이용 또는 삭제, 변경이 가능함 -- 과제 제출 시 본 주석
	 * 삭제 */

	if (a.first.first == b.first.first) {
		return a.first.second > b.first.second;
	}
	else {
		return a.first.first < b.first.first;
	}
}
