<?php
/**
 * @file
 * BDW_role_rules_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function BDW_role_rules_feature_default_rules_configuration() {
  $items = array();
  $items['rules_add_full_member_role_to_user_if_bda'] = entity_import('rules_config', '{ "rules_add_full_member_role_to_user_if_bda" : {
      "LABEL" : "Add \\u0022full member\\u0022 role to user if BDA",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } },
        { "flag_flagged_user" : {
            "flag" : "boondocking_available",
            "user" : [ "order:customer" ],
            "flagging_user" : [ "order:customer" ]
          }
        }
      ],
      "DO" : [
        { "user_add_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ]
    }
  }');
  $items['rules_add_membership_expired_role_to_user'] = entity_import('rules_config', '{ "rules_add_membership_expired_role_to_user" : {
      "LABEL" : "Add \\u0022membership expired\\u0022 role to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [
        { "OR" : [
            { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
            { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } }
          ]
        }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "18" : "18" } } } }
      ]
    }
  }');
  $items['rules_add_membership_expiring_flag_to_user'] = entity_import('rules_config', '{ "rules_add_membership_expiring_flag_to_user" : {
      "LABEL" : "Add \\u0022membership_expiring\\u0022 flag to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "flag_user" ],
      "REQUIRES" : [ "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_reminder" : [] },
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "membership_expiring",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_add_purchased_membership_flag_and_role_to_user'] = entity_import('rules_config', '{ "rules_add_purchased_membership_flag_and_role_to_user" : {
      "LABEL" : "Add \\u0022purchased membership\\u0022 flag and role to user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "flag_user" ],
      "REQUIRES" : [ "uc_order", "flag", "rules" ],
      "ON" : { "uc_order_status_update" : [] },
      "IF" : [
        { "uc_order_condition_has_product_class" : {
            "order" : [ "order" ],
            "product_classes" : { "value" : { "membership_level" : "membership_level" } },
            "required" : 0,
            "forbidden" : 0
          }
        },
        { "NOT uc_order_condition_order_state" : { "order" : [ "order" ], "order_state" : "completed" } },
        { "uc_order_condition_order_state" : { "order" : [ "updated-order" ], "order_state" : "completed" } }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "purchased_membership",
            "user" : [ "updated-order:customer" ],
            "flagging_user" : [ "updated-order:customer" ],
            "permission_check" : 0
          }
        },
        { "user_add_role" : {
            "account" : [ "updated-order:customer" ],
            "roles" : { "value" : { "20" : "20" } }
          }
        }
      ]
    }
  }');
  $items['rules_remove_expiring_membership_flag_from_user'] = entity_import('rules_config', '{ "rules_remove_expiring_membership_flag_from_user" : {
      "LABEL" : "Remove \\u0022membership_expiring\\u0022 flag from user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "flag_user" ],
      "REQUIRES" : [ "rules", "flag", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } },
        { "OR" : [] }
      ],
      "DO" : [
        { "flag_unflaguser" : {
            "flag" : "membership_expiring",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_remove_full_member_role_when_bda_req_role_is_revoked'] = entity_import('rules_config', '{ "rules_remove_full_member_role_when_bda_req_role_is_revoked" : {
      "LABEL" : "Remove \\u0022full member\\u0022 role when BDA req role is revoked",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "1",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "uc_roles" ],
      "ON" : { "uc_roles_notify_revoke" : [] },
      "IF" : [ { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "8" : "8" } } } }
      ]
    }
  }');
  $items['rules_remove_membership_expired_role_from_user'] = entity_import('rules_config', '{ "rules_remove_membership_expired_role_from_user" : {
      "LABEL" : "Remove \\u0022membership expired\\u0022 role from user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "flag_user" ],
      "REQUIRES" : [ "uc_order", "rules" ],
      "ON" : { "uc_order_status_update" : [] },
      "IF" : [
        { "uc_order_condition_has_product_class" : {
            "order" : [ "order" ],
            "product_classes" : { "value" : { "membership_level" : "membership_level" } },
            "required" : 0,
            "forbidden" : 0
          }
        },
        { "NOT uc_order_condition_order_state" : { "order" : [ "order" ], "order_state" : "completed" } },
        { "uc_order_condition_order_state" : { "order" : [ "updated-order" ], "order_state" : "completed" } }
      ],
      "DO" : [
        { "user_remove_role" : {
            "account" : [ "updated-order:customer" ],
            "roles" : { "value" : { "18" : "18" } }
          }
        }
      ]
    }
  }');
  $items['rules_remove_membership_expiring_flag_from_user'] = entity_import('rules_config', '{ "rules_remove_membership_expiring_flag_from_user" : {
      "LABEL" : "Remove \\u0022membership_expiring\\u0022 flag from user",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "flag_user" ],
      "REQUIRES" : [ "uc_order", "flag" ],
      "ON" : { "uc_order_status_update" : [] },
      "IF" : [
        { "uc_order_condition_has_product_class" : {
            "order" : [ "order" ],
            "product_classes" : { "value" : { "membership_level" : "membership_level" } },
            "required" : 0,
            "forbidden" : 0
          }
        },
        { "NOT uc_order_condition_order_state" : { "order" : [ "order" ], "order_state" : "completed" } },
        { "uc_order_condition_order_state" : { "order" : [ "updated-order" ], "order_state" : "completed" } }
      ],
      "DO" : [
        { "flag_unflaguser" : {
            "flag" : "membership_expiring",
            "user" : [ "updated-order:customer" ],
            "flagging_user" : [ "updated-order:customer" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_transfer_bda_req_membership_to_full_member_role'] = entity_import('rules_config', '{ "rules_transfer_bda_req_membership_to_full_member_role" : {
      "LABEL" : "Transfer BDA req membership to full member role",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "php", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "8" } },
        { "user_has_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "  $curtime = time();\\r\\n  $old_timestamp = $curtime;\\r\\n  $old_expirations = db_query(\\u0022SELECT expiration FROM {uc_roles_expirations} WHERE uid = %d AND rid = 13\\u0022, $order-\\u003Euid);\\r\\n  while ($old_expiration = db_fetch_object($old_expirations))\\r\\n  {\\r\\n    \\/\\/ there should really only be one entry, but for the benefit of the doubt,\\r\\n    \\/\\/ use the one with the greatest timestamp\\r\\n    if ($old_expiration-\\u003Eexpiration \\u003E $old_timestamp) {\\r\\n      $old_timestamp = $old_expiration-\\u003Eexpiration;\\r\\n    }\\r\\n  }\\r\\n\\r\\n  \\/\\/ determine how much time was left on the old role\\r\\n  $time_left = $old_timestamp - $curtime;\\r\\n  \\/\\/ add it to the new role\\r\\n  $new_timestamp = $expiration-\\u003Eexpiration + $time_left;\\r\\n  \\/\\/ write it to the expiration object and save to the DB.\\r\\n  $expiration-\\u003Eexpiration = $new_timestamp;\\r\\n  db_query(\\u0022UPDATE {uc_roles_expirations} SET expiration = %d WHERE uid = %d and rid = %d\\u0022, $new_timestamp, $order-\\u003Euid, $expiration-\\u003Erid);\\r\\n\\r\\n  \\/\\/ Delete the old expiration table entry without going through revoke (don\\u0027t want to trigger rules for it.)\\r\\n  $user = user_load($order-\\u003Euid);\\r\\n  uc_roles_delete($user, 13, TRUE);\\r\\n" } },
        { "user_remove_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "13" : "13" } }
          }
        }
      ]
    }
  }');
  $items['rules_transfer_full_membership_to_bda_req_role'] = entity_import('rules_config', '{ "rules_transfer_full_membership_to_bda_req_role" : {
      "LABEL" : "Transfer full membership to BDA req role",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "BDW_role_rules", "user_roles" ],
      "REQUIRES" : [ "rules", "php", "uc_roles" ],
      "ON" : { "uc_roles_notify_grant" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "expiration:rid" ], "value" : "13" } },
        { "user_has_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "  $curtime = time();\\r\\n  $old_timestamp = $curtime;\\r\\n  $old_expirations = db_query(\\u0022SELECT expiration FROM {uc_roles_expirations} WHERE uid = %d AND rid = 8\\u0022, $order-\\u003Euid);\\r\\n  while ($old_expiration = db_fetch_object($old_expirations))\\r\\n  {\\r\\n    \\/\\/ there should really only be one entry, but for the benefit of the doubt,\\r\\n    \\/\\/ use the one with the greatest timestamp\\r\\n    if ($old_expiration-\\u003Eexpiration \\u003E $old_timestamp) {\\r\\n      $old_timestamp = $old_expiration-\\u003Eexpiration;\\r\\n    }\\r\\n  }\\r\\n\\r\\n  \\/\\/ determine how much time was left on the old role\\r\\n  $time_left = $old_timestamp - $curtime;\\r\\n  \\/\\/ add it to the new role\\r\\n  $new_timestamp = $expiration-\\u003Eexpiration + $time_left;\\r\\n  \\/\\/ write it to the expiration object and save to the DB.\\r\\n  $expiration-\\u003Eexpiration = $new_timestamp;\\r\\n  db_query(\\u0022UPDATE {uc_roles_expirations} SET expiration = %d WHERE uid = %d and rid = %d\\u0022, $new_timestamp, $order-\\u003Euid, $expiration-\\u003Erid);\\r\\n\\r\\n  \\/\\/ Delete the old expiration table entry without going through revoke (don\\u0027t want to trigger rules for it.)\\r\\n  $user = user_load($order-\\u003Euid);\\r\\n  uc_roles_delete($user, 8, TRUE);\\r\\n" } },
        { "user_remove_role" : {
            "account" : [ "order:customer" ],
            "roles" : { "value" : { "8" : "8" } }
          }
        }
      ]
    }
  }');
  return $items;
}

function BDW_role_rules_feature_default_rules_configuration_alter(&$configs) {

foreach($configs['uc_role_notify_revoke']->actions() as $action)
{
  $action->settings['subject'] = t('Your membership at [store:name] has expired');
  $action->settings['message'] = t("Your membership at Boondockers Welcome has expired! Until you renew, you will no longer be able to send or receive messages, view your bookmarks, or leave recommendations for other members. Please renew your membership as soon as possible by visiting <a href='http://www.boondockerswelcome.com/membership-products'>our membership products page</a>.\n\nWe hope to see you back soon,\n\n[store:name]\n[site:slogan]"); 
}


foreach($configs['uc_checkout_admin_notification']->actions() as $action)
{
  $action->settings['addresses'] = 'admin@boondockerswelcome.com
marianne@boondockerswelcome.com';
}
  

  // disable uc_checkout_customer_notification - we will instead do this 
  // when the order goes into "complete". This will allow orders that are 
  // placed by hand (i.e. upgrades charges for $5, etc), to be invoiced as 
  // well as automated orders through the cart.
  $configs['uc_checkout_customer_notification']->active = 0;

  // disable default notify emails; expiry doesn't work.
  $configs['uc_role_notify_grant']->active = 0;
  $configs['uc_role_notify_renew']->active = 0;
  $configs['uc_role_notify_reminder']->active = 0;
}
