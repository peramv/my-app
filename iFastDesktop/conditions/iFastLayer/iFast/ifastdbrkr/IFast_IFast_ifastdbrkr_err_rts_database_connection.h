#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rts_database_connection : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rts_database_connection() { }
		~CIFast_IFast_ifastdbrkr_err_rts_database_connection() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RTS_DATABASE_CONNECTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("iFast Database connection error.  Please contact the service desk.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de connection à la base de données iFAST. Veuillez communiquer avec le centre de services.")); }

        // Actions
	};
}



