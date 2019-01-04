#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_disessn_diodbc_info : public CConditionObject
	{
	public:
		CBase_Ifds_disessn_diodbc_info() { }
		~CBase_Ifds_disessn_diodbc_info() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIODBC_INFO")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not authorized to modify field %TAG%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie sind nicht autorisiert, das Feld  %TAG% zu ändern.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Read-only fields cannot be updated.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Schreibgeschützte Felder können nicht aktualisiert werden.")); }
	};
}



