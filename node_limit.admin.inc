<?php
/**
 * @file
 * Administrative functions and forms for the Node Limit module. Admin forms found here are:
 *  Node Limits         - admin/structure/node_limit - X
 *  List                - admin/structure/node_limit/list - WTF?
 *  Add Node Limit      - admin/structure/node_limit/add
 *  Edit Node Limit     - admin/structure/node_limit/%node_limit
 *  Delete Node Limit   - admin/structure/node_limit/%node_limit/delete
 *  Clone Node Limit    - admin/structure/node_limit/%node_limit/clone
 *  Node Limit Settings - admin/structure/node_limit/settings - X
 */

/* ------------ Node Limits form ---------------- */
/**
 * Form for listing the created limits.
 * Created as a form so that the user can adjust the weight.
 */
function node_limit_list_limits() {
  // DA FUQ? -rositis
  $weights = array();

  for ($i = -10; $i <= 10; $i++) {
    $weights[$i] = $i;
  }

  $form = array('#tree' => TRUE);
  $form['limits'] = array();

  // @TODO: Convert to db_query for performance reasons.
  $query = db_select('node_limit', 'nl')
    ->fields('nl')
    ->orderBy('weight', 'ASC')
    ->execute();
  $nlimit = 0;
  foreach ($query as $row) {
    $nlimit++;
    $form['limits'][$row->lid]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $row->weight
    );
    $form['limits'][$row->lid]['title'] = array(
      '#markup' => check_plain($row->title)
    );
    $form['limits'][$row->lid]['limit'] = array(
      '#markup' => check_plain($row->nlimit)
    );
    $form['limits'][$row->lid]['edit'] = array('#type' => 'link', '#title' => t('Edit'), '#href' => 'admin/structure/node_limit/' . $row->lid);
    $form['limits'][$row->lid]['list'] = array('#type' => 'link', '#title' => t('Delete'), '#href' => 'admin/structure/node_limit/' . $row->lid . '/delete');
    $form['limits'][$row->lid]['clone'] = array('#type' => 'link', '#title' => t('Clone'), '#href' => 'admin/structure/node_limit/' . $row->lid . '/clone');
  }

  if ($nlimit > 0) {
    $form['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save Limits')
    );
  }
  else {
    $form['create'] = array(
      '#type' => 'link',
      '#title' => t('Add a new node limit'),
      '#href' => 'admin/structure/node_limit/add'
    );
  }

  return $form;
}

/**
 * Save the module weights.
 *
 * @param $form_id
 * @param $form_state
 */
function node_limit_list_limits_submit($form_id, &$form_state) {
  // @TODO: Change to db_query for performance reasons.
  foreach ($form_state['values']['limits'] as $lid => $info) {
    db_update('node_limit')
      ->fields(array(
        'weight' => $info['weight']
      ))
      ->condition('lid', $lid)
      ->execute();
  }
  backdrop_set_message(t('Limits saved!'));
}

/* ------------ Node Limit Add/Edit form ---------------- */
/**
 * Implements hook_form().
 */
function node_limit_limit_form($form, &$form_state, $limit = FALSE) {
  // If there isn't a value in $limit, it means we are adding a new Node Limit. Set the default values.
  if (empty($limit)) {
    $limit = array(
      'lid' => 0,
      'title' => '',
      'weight' => 0,
      'nlimit' => NODE_LIMIT_NO_LIMIT,
    );
  }

  // Put together the form.
  $form = array();
  $form['#tree'] = TRUE;
  if ($limit['lid'] > 0) {
    $form['lid'] = array(
      '#type' => 'hidden',
      '#value' => $limit['lid']
    );
  }

  $form['info']['title'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => $limit['title'],
    '#required' => TRUE,
    '#description' => t('The description for this Node Limit')
  );
  $form['info']['limit'] = array(
    '#title' => t('Limit'),
    '#type' => 'textfield',
    '#default_value' => (isset($limit['nlimit']) ? $limit['nlimit'] : NODE_LIMIT_NO_LIMIT),
    '#size' => 10,
    '#required' => TRUE,
    '#description' => t('The number of nodes for this limit.  Must be an integer greater than 0 or %no_limit for no limit', array('%no_limit' => NODE_LIMIT_NO_LIMIT))
  );
  $form['info']['weight'] = array(
    '#type' => 'hidden',
    '#value' => $limit['weight']
  );
  // @TODO: This is causing an issue when it tries to access the User Roles in the database.
  // @TODO: Figure out how this works with the API and how the submodules load this information.
  $elements = module_invoke_all('node_limit_element', $limit['lid']);
  $form['node_limit_elements'] = array();
  /*
  foreach ($elements as $module => $element) {
    $form['node_limit_elements'][$module]['applies'] = array(
      '#type' => 'checkbox',
      '#title' => check_plain($element['#title']),
      '#default_value' => isset($limit[$module])
    );
    $element['#title'] = '';
    $form['node_limit_elements'][$module]['element'] = $element;
  }
  */
  if (empty($form['node_limit_elements'])) {
    unset($form['node_limit_elements']);
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => ($limit['lid'] > 0?t('Edit Node Limit') : t('Add Node Limit'))
  );
  return $form;
}

/**
 * Validation hook for node_limit_limit_form.
 *
 * Allows submodules that are applied to validate their own input.
 */
function node_limit_limit_form_validate($form_id, &$form_state) {
  if (!is_numeric($form_state['values']['info']['limit'])) {
    form_set_error('info][limit', t('Node limits must be an integer'));
  }
  elseif (intval($form_state['values']['info']['limit']) != floatval($form_state['values']['info']['limit'])) {
    // Can't use is_int because is_int("2") == FALSE.
    form_set_error('info][limit', t('Node limits must be an integer'));
  }
  elseif (intval($form_state['values']['info']['limit']) < NODE_LIMIT_NO_LIMIT) {
    form_set_error('info][limit', t('Node limits cannot be less that %nolimit', array('%nolimit' => NODE_LIMIT_NO_LIMIT)));
  }

  if (trim($form_state['values']['info']['title']) == '') {
    form_set_error('info][title', t('Invalid Node Limit title'));
  }

  if (!empty($form_state['values']['node_limit_elements'])) {
    foreach ($form_state['values']['node_limit_elements'] as $module => $element) {
      if ($element['applies'] === 1) {
        // They checked the box!
        $result = module_invoke($module, 'node_limit_element_validate', $element['element']);
        if (is_array($result) && isset($result['error'])) {
          $path = $module . '][element';
          if (isset($result['element'])) {
            $path .= '][' . $result['element'];
          }
          form_set_error('node_limit_elements][' . $path, $result['error']);
        }
      }
    }
  }
}

/**
 * Submission hook for node_limit_limit_form.
 *
 * Calls the submission hook on applied submodules to allow them to save their data.
 */
function node_limit_limit_form_submit($form_id, &$form_state) {
  if (isset($form_state['values']['lid'])) {
    $lid = $form_state['values']['lid'];
  }
  else {
    $lid = _node_limit_next_limit_id();
  }
  $limit = array();
  $limit['lid'] = $lid;
  $limit['nlimit'] = intval($form_state['values']['info']['limit']);
  $limit['title'] = $form_state['values']['info']['title'];
  $limit['weight'] = $form_state['values']['info']['weight'];

  if (!empty($form_state['values']['node_limit_elements'])) {
    foreach ($form_state['values']['node_limit_elements'] as $module => $element) {
      if ($element['applies']) {
        $limit[$module] = $element['element'];
      }
    }
  }

  node_limit_save($limit);

  $form_state['redirect'] = 'admin/structure/node_limit';
  backdrop_set_message(t('Saved limit "%limit"', array('%limit' => $limit['title'])));
}

/* ------------ Node Limit Delete form ---------------- */
/**
 * Implements hook_form().
 * Confirmation form to delete a node limit.
 */
function node_limit_delete_form($form, &$form_state, $limit) {
  if ($limit == FALSE) {
    backdrop_goto('admin/structure/node_limit');
  }
  $form = array(
    'lid' => array(
      '#type' => 'hidden',
      '#value' => $limit['lid']
    )
  );
  return confirm_form($form, t('Are you sure you want to delete %name?', array('%name' => $limit['title'])), 'admin/structure/node_limit');
}

/**
 * Submission hook for node limit deletion.
 */
function node_limit_delete_form_submit($form_id, &$form_state) {
  $lid = $form_state['values']['lid'];
  node_limit_delete($lid);
  $form_state['redirect'] = 'admin/structure/node_limit';
}

/* ------------ Node Limits Clone callback ---------------- */
/**
 * Callback to clone a limit.
 *
 * @param $limit
 */
function node_limit_clone_limit($limit) {
  $old_title = $limit['title'];
  $limit['lid'] = _node_limit_next_limit_id();
  $limit['title'] = t('Clone of !title', array('!title' => $old_title));
  node_limit_save($limit);
  backdrop_set_message(t('Cloned limit "%limit"', array('%limit' => $old_title)));
  backdrop_goto('admin/structure/node_limit');
}

/* ------------ Node Limits Settings form ---------------- */
/**
 * Admin Form for Node Limit
 * Used
 * @param $form
 * @param $form_state
 *
 * @return array
 */
function node_limit_settings_form($form, &$form_state) {
  $form = array();
  $types = array();
  $config = config('node_limit.settings');

  // Get all content types on the site.
  $content_types = node_type_get_types();
  foreach ($content_types as $type) {
    $types[$type->type] = $type->name;
  }

  $form['node_limit_global_msg'] = array(
    '#type'  => 'textarea',
    '#title' => t('Global message'),
    '#required' => TRUE,
    '#description' => t('Available variables are: [node_limit:type_name], [node_limit:type_title]'),
    '#rows'  => 2,
    '#default_value' => $config->get('node_limit_global_msg'),
  );
  $form['node_limit_global_redirect'] = array(
    '#type'  => 'textfield',
    '#title' => t('Global redirect path'),
    '#default_value' => $config->get('node_limit_global_redirect'),
    '#description'   => t("Available variables are: [node_limit:type_name], [node_limit:type_title] (Leave empty if you don't need redirect)"),
  );

  if (!empty($types)) {
    $form['node_limit_custom_msg'] = array(
      '#type'  => 'checkbox',
      '#title' => t('Enable custom error message'),
      '#default_value' => $config->get('node_limit_custom_msg'),
    );
  }

  foreach ((array) $types as $machine_name => $title) {
    // @TODO: Set this default in the node_limit_install() function.
    // @TODO: This might be problematic if this is a new node type. Consider how to implement updating that.
    // @TODO: Perhaps this should be added to the node.settings.
    $settings = config_get('node_limit_settings_' . $machine_name);
    $form['custom_msg']['node_limit_settings_' . $machine_name] = array(
      '#type'  => 'fieldset',
      '#title' => $title,
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
      '#tree'   => TRUE,
      '#states' => array(
        'visible' => array(
          ':input[name="node_limit_custom_msg"]' => array('checked' => TRUE),
        ),
      ),
    );
    $form['custom_msg']['node_limit_settings_' . $machine_name]['message_' . $machine_name] = array(
      '#type'  => 'textarea',
      '#title' => t('Message'),
      '#rows'  => 2,
      '#default_value' => $settings['message_' . $machine_name],
    );
    $form['custom_msg']['node_limit_settings_' . $machine_name]['redirect_' . $machine_name] = array(
      '#type'  => 'textfield',
      '#title' => t('Redirect path'),
      '#default_value' => $settings['redirect_' . $machine_name],
    );
  }

  // Buttons
  $form['buttons'] = array(
    '#type' => 'container',
  );

  // Submit button
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
* Admin form validation.
 *
 * @param $form
 * @param $form_state
 */
function node_limit_settings_form_validate($form, &$form_state) {
  /*
  if (strpos($form_state['triggering_element']['#id'], 'remove') === FALSE) {
    $breakpoints = isset($form_state['values']['breakpoints']) ? $form_state['values']['breakpoints'] : array();
    if (!empty($breakpoints)) {
      foreach ($breakpoints as $key => $breakpointdata) {
        if (!empty($breakpointdata['name'])) {
          // Breakpoint is required.
          if ($key == 'new') {
            if (empty($breakpointdata['machine_name'])) {
              form_set_error('breakpoints][' . $key . '][machine_name', 'Machine name field is required');
            }
          }
        }
      }
    }
  }
  */
}

/**
 * Admin form submit.
 *
 * @param $form
 * @param $form_state
 */
function node_limit_settings_form_submit($form, &$form_state) {
  /*
  $breakpoints = $form_state['values']['breakpoints'];
  $group_name = $form_state['group_name'];
  $global_group = $group_name == '';
  $group = breakpoints_breakpoint_group_empty_object();
  if (!$global_group) {
    // sort by weight, needed to store the right order in a group
    uasort($breakpoints, '_breakpoints_sort_by_weight_array');
  }
  $saved_breakpoints = array();
  if (!empty($breakpoints)) {
    foreach ($breakpoints as $breakpointname => $breakpointdata) {
      if (!empty($breakpointdata['name'])) {
        $breakpoint = breakpoints_breakpoint_load_by_fullkey($breakpointname);
        if ($breakpoint && $breakpointname != 'new') {
          // only save the weight when on the global screen.
          if ($global_group) {
            $breakpoint->weight = $breakpointdata['weight'];
          }
          else {
            $breakpoint->weight = $breakpointdata['global_weight'];
          }
          $breakpoint->breakpoint = $breakpointdata['breakpoint'];
          $breakpoint->multipliers = isset($breakpointdata['multipliers']) ? $breakpointdata['multipliers'] : array();
          breakpoints_breakpoint_save($breakpoint);
          $saved_breakpoints[] = $breakpointname;
        }
        else {
          $breakpoint = new stdClass();
          $breakpoint->name = $breakpointdata['name'];
          $breakpoint->breakpoint = $breakpointdata['breakpoint'];
          $breakpoint->source = 'user';
          $breakpoint->source_type = 'custom';
          $breakpoint->weight = $breakpointdata['weight'];
          $breakpoint->status = TRUE;
          $breakpoint->multipliers = isset($breakpointdata['multipliers']) ? $breakpointdata['multipliers'] : array();
          $breakpoint->machine_name = 'custom.user.' . $breakpointdata['machine_name'];
          breakpoints_breakpoint_save($breakpoint);
          $saved_breakpoints[] = breakpoints_breakpoint_config_name($breakpoint);
        }
      }
    }
    if (!$global_group) {
      $group = breakpoints_breakpoint_group_load($group_name);
      if ($group) {
        $group->breakpoints = $saved_breakpoints;
        breakpoints_breakpoint_group_save($group);
      }
    }
  }
  */
}


