#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_malformed_dstc_response_buffer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_malformed_dstc_response_buffer() { }
		~CIFast_IFast_ifastdbrkr_err_malformed_dstc_response_buffer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MALFORMED_DSTC_RESPONSE_BUFFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Host response buffer for request %REQID% is malformed at position %POSITION%.  Expecting: %EXPECTED%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Host-Antwort-Buffer für Anfrage %REQID% ist fehlerhaft bei Position %POSITION%. Erwartet wird %EXPECTED%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El búfer de respuesta del host para la solicitud %REQID%  está mal formado en la posición %POSITION%. Se esperaba %EXPECTED%:.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mémoire tampon de réponse de l'hôte pour la requête %REQID% est malformée en position %POSITION%.  Prévision : %EXPECTED%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De responsbuffer van de host voor opdracht %REQID%  is misvormd op positie %POSITION%. Verwacht %EXPECTED%:")); }

        // Actions
	};
}



