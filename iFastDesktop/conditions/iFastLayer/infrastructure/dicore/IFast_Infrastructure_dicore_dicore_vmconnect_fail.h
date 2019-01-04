﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_vmconnect_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_vmconnect_fail() { }
		~CIFast_Infrastructure_dicore_dicore_vmconnect_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMCONNECT_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmAppConnect error.  Return Code: %RC%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmAppConnect error.  Return Code: %RC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmAppConnect-Fehler.  Rückgabecode: %RC%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de VmAppConnect.  Código de retorno: %RC%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de connexion à l'application du gestionnaire de l'affichage. Code de renvoi : %RC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmAppConnect fout.  Retourcode: %RC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



