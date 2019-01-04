#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batch_cannot_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batch_cannot_be_blank() { }
		~CIFast_IFast_ifastdbrkr_err_batch_cannot_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCH_CANNOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch Name cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch Name cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch-Name darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El nombre de lote no puede estar en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Nom du lot doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batchnaam kan niet leeg zijn")); }

        // Actions
	};
}



