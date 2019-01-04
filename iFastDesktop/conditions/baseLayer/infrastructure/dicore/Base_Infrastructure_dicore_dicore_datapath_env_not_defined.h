#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_datapath_env_not_defined : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_datapath_env_not_defined() { }
		~CBase_Infrastructure_dicore_dicore_datapath_env_not_defined() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATAPATH_ENV_NOT_DEFINED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. This workstation has not been properly setup with the required environmental variables!")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. This workstation has not been properly setup with the required environmental variables!")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Diese Workstation wurde nicht mit den erforderlichen Umgebungsvariablen gestartet!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. ¡No se ha configurado la estación de trabajo correctamente con las variables de entorno requeridas!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Ce poste de travail n'a pas été convenablement réglé avec les variables environnementales requises.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Het werkstation is niet goed ingesteld met de vereiste omgevingsvariabelen!")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative to verify install configuration.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter, um die Installationskonfiguration zu überprüfen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Póngase en contacto con un representante de soporte técnico para verificar la configuración de instalación.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique pour vérifier la configuration de l'installation.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker om de installatieconfiguratie te controleren")); }
	};
}



