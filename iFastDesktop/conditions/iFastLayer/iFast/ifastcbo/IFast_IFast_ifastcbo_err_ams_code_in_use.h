#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_code_in_use : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_code_in_use() { }
		~CIFast_IFast_ifastcbo_err_ams_code_in_use() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_CODE_IN_USE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You may not delete this record. Accounts still exist with this AMS Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Löschen Sie diesen Eintrag nicht. Es existieren immer noch Konten mit diesem AMS-Code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar este registro. Aún existen cuentas con este código AMS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous ne pouvez pas supprimer cet enregistrement. Des comptes existent encore avec ce code de service de gestion de portefeuille.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U mag dit record niet wissen. Er zijn nog accounts met deze BBD-code")); }

        // Actions
	};
}



