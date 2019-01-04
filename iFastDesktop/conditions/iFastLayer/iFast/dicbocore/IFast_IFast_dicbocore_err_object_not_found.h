#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_object_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_object_not_found() { }
		~CIFast_IFast_dicbocore_err_object_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax type of this account is not allowed for PAC allocation set up.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Tax type of this account is not allowed for PAC allocation set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Steuerart dieses Kontos ist nicht für PAC-Zuweisungserstellung zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el tipo tributario de esta cuenta para la configuración de asignación PAC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'imposition de ce compte n'est pas autorisé pour le réglage de la répartition PAC.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype van dit account is niet toegestaan voor de instelling van een VGC-allocatie")); }

        // Actions
	};
}



