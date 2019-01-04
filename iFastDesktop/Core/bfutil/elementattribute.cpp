#include "stdafx.h"

#include "elementattribute.hpp"

ElementAttribute::~ElementAttribute()
{}

BasicElementAttribute::BasicElementAttribute( const DString &tag, const DString &value )
: _tag(tag)
, _value(value)
{
}

BasicElementAttribute::~BasicElementAttribute()
{}

//******************************************************************************
ElementAttribute *BasicElementAttribute::clone() const
{
   return(new BasicElementAttribute(*this));
}

//******************************************************************************
const DString &BasicElementAttribute::getTagName() const
{
   return(_tag);
}

//******************************************************************************
const DString &BasicElementAttribute::getValue() const
{
   return(_value);
}

//******************************************************************************
bool BasicElementAttribute::hasDefaultValue() const
{
   return(false);
}
