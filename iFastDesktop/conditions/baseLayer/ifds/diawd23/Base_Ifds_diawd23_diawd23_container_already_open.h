#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawd23_diawd23_container_already_open : public CConditionObject
	{
	public:
		CBase_Ifds_diawd23_diawd23_container_already_open() { }
		~CBase_Ifds_diawd23_diawd23_container_already_open() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_CONTAINER_ALREADY_OPEN")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Privatverbindungsfehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de connexion privée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout privé-verbinding")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("NULL")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("NULL")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("NULL")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("NUL")); }
	};
}



