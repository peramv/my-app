#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_nominee_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_nominee_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_multiple_nominee_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_NOMINEE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Nominee Owner entities not allowed on accounts.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les entites Proprietaires nominaux (21) ne sont pas autorisées pour les comptes.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrfache Bevollmächtigte Eigentümer (21) nicht erlaubt für Konten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten las entidades propietario nominatario múltiples (21) en las cuentas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les entités à propriétaires nominés multiples ne sont pas autorisées à accéder aux comptes.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Meerdere eenheden voor gemachtigde eigenaar (21) zijn niet toegestaan in accounts")); }

        // Actions
	};
}



