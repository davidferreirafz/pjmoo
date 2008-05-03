#ifndef UINUMBERFIELD_H
#define UINUMBERFIELD_H

#include "UIField.h"


class UINumberField : public UIField
{
  public:
    UINumberField();
    virtual ~UINumberField();

    void setValue(unsigned int value);

  protected:
    void desenharConteudo();

  private:
    unsigned int value;
};

#endif // UINUMBERFIELD_H
