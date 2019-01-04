#include "stdafx.h"

#include "elementattribute.hpp"

ElementAttribute::~ElementAttribute()
{}

BasicElementAttribute::BasicElementAttribute( const std::string &tag, const std::string &value )
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
const std::string &BasicElementAttribute::getTagName() const
{
   return(_tag);
}

//******************************************************************************
const std::string &BasicElementAttribute::getValue() const
{
   return(_value);
}

//******************************************************************************
bool BasicElementAttribute::hasDefaultValue() const
{
   return(false);
}
