#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_vmrequest_init_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_vmrequest_init_fail() { }
		~CIFast_Infrastructure_dicore_dicore_vmrequest_init_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMREQUEST_INIT_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmRequest initialization error.  Lower-level error: %ERROR%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmRequest initialization error.  Lower-level error: %ERROR%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmRequest-Initialisierungs-Fehler.  Fehler auf niedriger Ebene: %ERROR%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de inicialización de VmRequest.  Error de nivel inferior: %ERROR%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'initialisation de demande de gestionnaire de l'affichage. Erreur de niveau inférieur : %ERROR%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmRequest-initialisatiefout.  Fout op lager niveau: %ERROR%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check AWD View setup.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check AWD View setup.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Setup der AWD-Ansicht.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique la configuración de view AWD.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le réglage de l'affichage AWD.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de instelling van de AWD-view")); }
	};
}



