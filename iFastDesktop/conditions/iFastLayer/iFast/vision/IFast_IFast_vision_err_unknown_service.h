#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_unknown_service : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_unknown_service() { }
		~CIFast_IFast_vision_err_unknown_service() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_SERVICE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The server cannot determine the service required")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The server cannot determine the service required")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Server kann den notwendigen Service nicht bestimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El servidor no puede determinar el servicio requerido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le serveur ne peut déterminer le service requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De server kan de gewenste sessie niet vaststellen")); }

        // Actions
	};
}



