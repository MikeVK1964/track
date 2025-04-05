#ifndef SETCONTROL_H
#define SETCONTROL_H

class SetControl
{
public:
  SetControl();
  int dist; // дистанция ИКО
  int h;  // Высота СИ
  int status; // 1- имитация
  int v_imi;  // значение в комбобокс

};

#endif // SETCONTROL_H
