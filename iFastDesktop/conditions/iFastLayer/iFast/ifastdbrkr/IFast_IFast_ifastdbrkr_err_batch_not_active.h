#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_batch_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_batch_not_active() { }
		~CIFast_IFast_ifastdbrkr_err_batch_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BATCH_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Batch is not active or does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Batch is not active or does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch ist nicht aktiv oder existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El lote no está activo o no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le lot est inactif ou n'existe pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Batch is niet actief of bestaat niet")); }

        // Actions
	};
}



