#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_field_is_over_maximum_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_field_is_over_maximum_allowed() { }
		~CIFast_IFast_dicbocore_err_field_is_over_maximum_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_IS_OVER_MAXIMUM_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocations cannot be set up for inactive accounts.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocations may not be set up for inactive accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisungen können nicht für inaktive Konten erstellt werden. Bitte wählen Sie ein aktives Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No pueden configurarse asignaciones para las cuentas inactivas.  Por favor vuelva a seleccionar una cuenta activa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions ne peuvent être réglées pour des comptes inactifs.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocaties kunnen niet worden ingesteld voor inactieve accounts. Selecteer een actief account")); }

        // Actions
	};
}



