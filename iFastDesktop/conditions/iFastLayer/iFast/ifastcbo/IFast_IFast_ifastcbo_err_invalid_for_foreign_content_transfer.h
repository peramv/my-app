#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_for_foreign_content_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_for_foreign_content_transfer() { }
		~CIFast_IFast_ifastcbo_err_invalid_for_foreign_content_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FOR_FOREIGN_CONTENT_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid fund for Foreign sweeps excess transfer.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid fund for Foreign sweeps excess transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Fonds für Auslands-Giro-Überschuss-Transfer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fondo no válido para transferencias automáticas de excedente extranjero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds invalide pour le transfert d'excédent du niveau de contenu étranger")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig fonds voor surplusoverdracht buitenlandse ?Sweep-accounts?")); }

        // Actions
	};
}



