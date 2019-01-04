#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfutil_bfutil_no_host_codepage : public CConditionObject
	{
	public:
		CBase_Ifds_bfutil_bfutil_no_host_codepage() { }
		~CBase_Ifds_bfutil_bfutil_no_host_codepage() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BFUTIL_NO_HOST_CODEPAGE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfutil")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Host Code Page was not specified in the registry")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart kann nicht geändert werden – für dieses Konto existieren Transaktionen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The Host Code Page was not specified in the registry")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La page de code de l'hôte n'a pas été spécifiée dans le registre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The Host Code Page was not specified in the registry")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter an appropriate value in the registry value [AppName]\\Config\\RTSHost\\Codepage")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Enter an appropriate value in the registry value [AppName]\\Config\\RTSHost\\Codepage")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter an appropriate value in the registry value [AppName]\\Config\\RTSHost\\Codepage")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur appropriée dans la valeur d'enregistrement  [AppName]\\Config\\RTSHost\\Codepage")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Enter an appropriate value in the registry value [AppName]\\Config\\RTSHost\\Codepage")); }
	};
}



