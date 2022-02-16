#include "Manager.h"

/*  �� ���� ���� �� �� �ּ� ����
���� ���Ǽ��� ���� �Ϻ� �Լ��� �ڵ尡 �ۼ��Ǿ� ������, �ش� �ڵ�� �̿� �Ǵ�
����, ������ ������. ����, �Ϻ� �ڵ�� ���� �䱸���׿� �°� ������ �ʿ��� ��
���� (��: �ܼ� ��� -> ���� ���) �� ��, ������ ������Ʈ ������ Ŭ����, ���
����, ��� �Լ��� �̸��� ������ ���� �Ұ��� �� ������ �Լ����� �ڵ带 �״��
�̿��� ���, �ٽ� �ڵ忡�� �ݵ�� �ּ� �߰�
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
	/* �Ʒ� �ۼ��� �ڵ�� �̿� �Ǵ� ����, ������ ������ -- ���� ���� �� �� �ּ�
	 * ���� */

	if (a.first.first == b.first.first) {
		return a.first.second > b.first.second;
	}
	else {
		return a.first.first < b.first.first;
	}
}
