#include <iostream>


#include "VendingMachine.h"


int main() {
  Snack* bounty = new Snack("Bounty");
  Snack* snickers = new Snack("Snickers");
  SnackSlot* slot = new SnackSlot(10/*���������� ����������, ������� ���������� � ����*/);
  slot->addSnack(bounty); //��������� �������� � ����
  slot->addSnack(snickers);
  int slotCount = 10;
  VendingMachine* machine = new VendingMachine(slotCount /*���������� ������ ��� ������*/);
  machine->addSlot(slot); // �������� ���� ������� � �������

  std::cout << machine->getEmptySlotsCount(); // ������ �������� ���������� ������ ������ ��� ������
  delete machine;
  delete slot;
  delete snickers;
  delete bounty;
}