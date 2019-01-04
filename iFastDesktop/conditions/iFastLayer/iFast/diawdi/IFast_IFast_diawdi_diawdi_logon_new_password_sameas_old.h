#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawdi_diawdi_logon_new_password_sameas_old : public CConditionObject
	{
	public:
		CIFast_IFast_diawdi_diawdi_logon_new_password_sameas_old() { }
		~CIFast_IFast_diawdi_diawdi_logon_new_password_sameas_old() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one ID Type must be entered for each entity.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins un type d'itentification doit être saisi pour chaque entite.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es muss wenigstens ein ID-Typ für jedes Objekt eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse al menos un tipo de identificación para cada entidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un type de code est requis pour chaque entité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één ID-type worden ingevoerd voor elke eenheid")); }

        // Actions
	};
}



