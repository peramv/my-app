#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawd23_diawd23_relate_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawd23_diawd23_relate_fail() { }
		~CIFast_IFast_diawd23_diawd23_relate_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_RELATE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No %service% to end for this user")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No %service% to end for this user")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein %service% zu beenden durch diesen Benutzer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay %service% para terminar para este usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun service %service% auquel mettre fin pour cet utilisateur")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kan geen %service% worden beëindigd voor deze gebruiker")); }

        // Actions
	};
}



