#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_joint_information_only_for_joint_accounts : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_joint_information_only_for_joint_accounts() { }
		~CIFast_Infrastructure_ifastdbrkr_err_joint_information_only_for_joint_accounts() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_JOINT_INFORMATION_ONLY_FOR_JOINT_ACCOUNTS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Audit file bad open.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Audit file bad open.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prüfungsdatei nicht richtig geöffnet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Archivo de auditoría no válido abierto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le dossier de vérification s'est mal ouvert.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Auditbestand is niet goed geopend")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



