#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdbrkr_err_privconn_create_event : public CConditionObject
	{
	public:
		CBase_Ifds_bfdbrkr_err_privconn_create_event() { }
		~CBase_Ifds_bfdbrkr_err_privconn_create_event() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_CREATE_EVENT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Privatverbindungsfehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Private connection error")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une erreur s'est produite lors de la tentative de connexion à l'hôte en utilisant une connection privée au gestionnaire de l'affichage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("An error occured while attempting to connect to host using VM private connection")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("NULL")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("NULL")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



