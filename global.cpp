#include "global.h"
std::function<void(QWidget*)> repolishErrorQSS = [](QWidget*widget){
    widget->style()->unpolish(widget); //remove old propertity
    widget->style()->polish(widget);   //add new propertity
};
QString gate_url_prefix = "";
