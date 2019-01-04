#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_disessn_disessn_default_label_used : public CConditionObject
	{
	public:
		CIFast_Infrastructure_disessn_disessn_default_label_used() { }
		~CIFast_Infrastructure_disessn_disessn_default_label_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DISESSN_DEFAULT_LABEL_USED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A configuration setting is invalid. Label for data is not defined in the configuration because a default was used.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A configuration setting is invalid. Label for data is not defined in the configuration because a default was used.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine Konfigurationseinstellung ist ungültig. Die Datenbezeichnung ist in der Konfiguration nicht definiert, da ein Standardwert verwendet wurde.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un parámetro de configuración no válido. La etiqueta de datos no está definida en la configuración porque se utilizó un parámetro predeterminado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un réglage de la configuration est invalide. L'étiquette de données n'est pas définie dans la configuration parce qu'une valeur par défaut à été utilisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ongeldige configuratie-instelling. Label voor gegevens is niet gedefinieerd in de configuratie omdat er een standaardlabel is gebruikt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



