#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_element_class_attribute_not_specified : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_element_class_attribute_not_specified() { }
		~CBase_Infrastructure_xparser_err_element_class_attribute_not_specified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ELEMENT_CLASS_ATTRIBUTE_NOT_SPECIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Machine is out of memory. There is insufficient disc space.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Machine is out of memory. There is insufficient disc space.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Computer kann nicht mehr speichern. Es gibt nicht genügend Platz auf der Festplatte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La máquina se quedó sin memoria. No hay suficiente espacio en el disco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La machine n'a plus de mémoire. L'espace sur le disque est insuffisant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Machine heeft geen geheugen meer. Er is onvoldoende schijfruimte")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



