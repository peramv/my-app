﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unknown_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unknown_error() { }
		~CIFast_IFast_ifastdbrkr_err_unknown_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Erreur inconnue.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekannter Fehler")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur inconnue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende fout")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



