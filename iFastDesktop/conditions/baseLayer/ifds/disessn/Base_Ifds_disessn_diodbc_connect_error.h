#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_disessn_diodbc_connect_error : public CConditionObject
	{
	public:
		CBase_Ifds_disessn_diodbc_connect_error() { }
		~CBase_Ifds_disessn_diodbc_connect_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIODBC_CONNECT_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt %OBJECT% wurde nicht registriert.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
	};
}



