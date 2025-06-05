#ifndef SETCONTROL_H
#define SETCONTROL_H

class SetControl
{
public:
  SetControl();
  int dist; // дистанция ИКО
  int h;  // Высота СИ
  int status; // 0 - нет имитации 1- имитация 2 - имитация + сеть
  int v_imi;  // значение в комбобокс

};

#endif // SETCONTROL_H
