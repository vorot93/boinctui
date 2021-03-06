// =============================================================================
// This file is part of boinctui.
// http://boinctui.googlecode.com
// Copyright (C) 2012,2013 Sergey Suslov
//
// boinctui is free software; you can redistribute it and/or modify it  under
// the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// boinctui is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details
// <http://www.gnu.org/licenses/>.
// =============================================================================

#include <stdio.h>
#include "ncolorstring.h"


NColorStringPart::NColorStringPart(int attr, const char* fmt, va_list vl)
{
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt, vl);
    this->s = buf;
    this->attr = attr;
}


NColorString::NColorString(int attr, const char* fmt, ...)
{
    va_list	args;
    va_start(args, fmt);
    vappend(attr,fmt,args);
    va_end(args);
}


NColorString::NColorString(int attr, const char* fmt, va_list vl)
{
    vappend(attr,fmt,vl);
}


NColorString::~NColorString()
{
    std::list<NColorStringPart*>::iterator it;
    for (it = parts.begin(); it != parts.end(); it++)
    {
	delete (*it);
    }
}


void NColorString::append(int attr, const char* fmt, ...)
{
    va_list	args;
    va_start(args, fmt);
    NColorStringPart* part = new NColorStringPart(attr, fmt, args);
    va_end(args);
    append(part);
}


void NColorString::vappend(int attr, const char* fmt, va_list vl)
{
    NColorStringPart* part = new NColorStringPart(attr, fmt, vl);
    append(part);
}


int NColorString::getlen()  //вернет длинну в ЭКРАННЫХ СИМВОЛАХ
{
    int result = 0;
    std::list<NColorStringPart*>::iterator it;
    for (it = parts.begin(); it != parts.end(); it++)
    {
	result = result + (*it)->getlen();
    }
    return result;
}


NColorString& NColorString::operator=(const NColorString& v)
{
    clear();
    std::list<NColorStringPart*>::const_iterator it;
    for ( it = v.parts.begin(); it != v.parts.end(); it++ )
    {
	append((*it)->attr, (*it)->s.c_str());
    }
    return *this;
}


bool NColorString::operator==(const NColorString& v)
{
    bool result = true;
    if (v.parts.size() != parts.size())
	return false; //различается кол-во эл-тов
    //сравниваем поэлементно
    std::list<NColorStringPart*>::const_iterator it1;
    std::list<NColorStringPart*>::const_iterator it2;
    it2 = v.parts.begin();
    for ( it1 = parts.begin(); it1 != parts.end(); it1++ )
    {
	if (*(*it1) == *(*it2))
	    it2++;
	else
	    return false; //часть отличается
    }
    return result;
}


