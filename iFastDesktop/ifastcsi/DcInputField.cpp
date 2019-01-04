// DcInputField.cpp: implementation of the DcInputField class.
//
//////////////////////////////////////////////////////////////////////

#include "DcInputField.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DcInputField::DcInputField(const std::string &componentName, int row, int column, int tabOrder)
:CsiComponent(componentName), _row(row), _column(column), _tabOrder(tabOrder)
{

}

DcInputField::~DcInputField()
{

}
