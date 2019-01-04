﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_object_read_only : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_object_read_only() { }
		~CBase_Infrastructure_dicbocore_err_object_read_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_READ_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not authorized to update %OBJECT% object.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not authorized to update '^' object.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie sind nicht autorisiert, das Objekt  %OBJEKT% zu aktualisieren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No está autorizado a actualizar el objeto  %OBJECT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Non autorisé à mettre à jour l'objet %OBJECT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Niet gemachtigd om object %OBJECT% bij te werken")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Read-only objects cannot be updated.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Read-only objects cannot be updated.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Schreibgeschützte Objekte können nicht aktualisiert werden.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Read-only objects cannot be updated.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les objets à lecture seule ne peuvent être mis à jour.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("De objecten die alleen kunnen worden gelezen, kunnen niet worden bijgewerkt")); }
	};
}



