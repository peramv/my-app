#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_wrn_line_number : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_wrn_line_number() { }
		~CBase_Infrastructure_ditabuscore_wrn_line_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WRN_LINE_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid line number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid line number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Zeilenzahl.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de línea no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de ligne invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig regelnummer")); }

        // Actions
	};
}



