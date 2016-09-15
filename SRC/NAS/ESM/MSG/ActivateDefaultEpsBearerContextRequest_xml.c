/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under 
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>

#include <libxml/xmlwriter.h>
#include <libxml/xpath.h>
#include "bstrlib.h"

#include "hashtable.h"
#include "obj_hashtable.h"
#include "log.h"
#include "common_defs.h"
#include "ActivateDefaultEpsBearerContextRequest.h"
#include "ActivateDefaultEpsBearerContextRequest_xml.h"
#include "3gpp_24.008_xml.h"

//------------------------------------------------------------------------------
bool activate_default_eps_bearer_context_request_from_xml (
    xmlDocPtr                         xml_doc,
    xmlXPathContextPtr                xpath_ctx,
    activate_default_eps_bearer_context_request_msg * activate_default_eps_bearer_context_request)
{
  OAILOG_FUNC_IN (LOG_NAS_ESM);
  memset(activate_default_eps_bearer_context_request, 0, sizeof(*activate_default_eps_bearer_context_request));
  bool res = false;

  res = eps_quality_of_service_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->epsqos);
  if (res) {res = access_point_name_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->accesspointname);}
  if (res) {res = pdn_address_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->pdnaddress);}

  if (res) {
    res = linked_ti_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->transactionidentifier);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_TRANSACTION_IDENTIFIER_PRESENT;
    }

    res = quality_of_service_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->negotiatedqos);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_NEGOTIATED_QOS_PRESENT;
    }

    res = llc_service_access_point_identifier_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->negotiatedllcsapi);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_NEGOTIATED_LLC_SAPI_PRESENT;
    }

    res = radio_priority_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->radiopriority);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_RADIO_PRIORITY_PRESENT;
    }

    res = packet_flow_identifier_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->packetflowidentifier);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_PACKET_FLOW_IDENTIFIER_PRESENT;
    }

    res = apn_aggregate_maximum_bit_rate_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->apnambr);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_APNAMBR_PRESENT;
    }

    res = esm_cause_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->esmcause);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_ESM_CAUSE_PRESENT;
    }

    res = protocol_configuration_options_from_xml (xml_doc, xpath_ctx, &activate_default_eps_bearer_context_request->protocolconfigurationoptions, false);
    if (res) {
      activate_default_eps_bearer_context_request->presencemask |= ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT;
    }
    res = true;
  }
  OAILOG_FUNC_RETURN (LOG_NAS_ESM, res);
}

//------------------------------------------------------------------------------
int activate_default_eps_bearer_context_request_to_xml (
  activate_default_eps_bearer_context_request_msg * activate_default_eps_bearer_context_request,
  xmlTextWriterPtr writer)
{
  OAILOG_FUNC_IN (LOG_NAS_ESM);

  eps_quality_of_service_to_xml (&activate_default_eps_bearer_context_request->epsqos, writer);

  access_point_name_to_xml (activate_default_eps_bearer_context_request->accesspointname, writer);

  pdn_address_to_xml (&activate_default_eps_bearer_context_request->pdnaddress, writer);

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_TRANSACTION_IDENTIFIER_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_TRANSACTION_IDENTIFIER_PRESENT) {
    linked_ti_to_xml (&activate_default_eps_bearer_context_request->transactionidentifier, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_NEGOTIATED_QOS_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_NEGOTIATED_QOS_PRESENT) {
    quality_of_service_to_xml (&activate_default_eps_bearer_context_request->negotiatedqos, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_NEGOTIATED_LLC_SAPI_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_NEGOTIATED_LLC_SAPI_PRESENT) {
    llc_service_access_point_identifier_to_xml (&activate_default_eps_bearer_context_request->negotiatedllcsapi, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_RADIO_PRIORITY_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_RADIO_PRIORITY_PRESENT) {
    radio_priority_to_xml (&activate_default_eps_bearer_context_request->radiopriority, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_PACKET_FLOW_IDENTIFIER_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_PACKET_FLOW_IDENTIFIER_PRESENT) {
    packet_flow_identifier_to_xml (&activate_default_eps_bearer_context_request->packetflowidentifier, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_APNAMBR_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_APNAMBR_PRESENT) {
    apn_aggregate_maximum_bit_rate_to_xml (&activate_default_eps_bearer_context_request->apnambr, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_ESM_CAUSE_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_ESM_CAUSE_PRESENT) {
    esm_cause_to_xml (&activate_default_eps_bearer_context_request->esmcause, writer);
  }

  if ((activate_default_eps_bearer_context_request->presencemask & ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT)
      == ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST_PROTOCOL_CONFIGURATION_OPTIONS_PRESENT) {
    protocol_configuration_options_to_xml (&activate_default_eps_bearer_context_request->protocolconfigurationoptions, writer, false);
  }
  OAILOG_FUNC_RETURN (LOG_NAS_ESM, RETURNok);
}
