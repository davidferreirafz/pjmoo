#ifndef UITEXTFIELD_H
#define UITEXTFIELD_H

#include <GBF/UserInterfaceComponente.h>
#include <GBF/GraphicSystemUtility.h>
#include <GBF/TimerSystemCronometroCrescente.h>

#include "UIField.h"
#include "UI.h"

class UITextField: public UIField
{
  public:
    UITextField();
    virtual ~UITextField();
    void setValue(std::string value);

  protected:
    void desenharConteudo();

  private:
    std::string value;


};

#endif // UITEXTFIELD_H
