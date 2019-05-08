<?php

/**
 * @file
 * Administrations pages callbacks for the Jobvite module.
 */

/**
 * Implements hook_form().
 */
function jobvite_admin_form($form, &$form_state) {

  $form['jobvite_api_information'] = array(
    '#markup' => t("<p>This settings page allows you to configure the Jobvite module. You have a part for generic informations for the Jobvite API and an other to filter imported jobs.<br/>Please, report you to the <em>Jobvite Web Service - Version 2.5 – February 6, 2013.pdf</em> API's documentation of Jobvite for more informations.</p>"),
  );

  $form['jobvite_infos'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connection informations'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['jobvite_infos']['jobvite_api'] = array(
    '#type' => 'textfield',
    '#title' => t('Api key'),
    '#required' => TRUE,
    '#default_value' => variable_get('jobvite_api', ""),
    '#description' => t('Your API key to access datas of your company'),
  );

  $form['jobvite_infos']['jobvite_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key for Jobvite'),
    '#required' => TRUE,
    '#default_value' => variable_get('jobvite_secret_key', ""),
    '#description' => t('Your secret key to access datas of your company'),
  );

  $form['jobvite_infos']['jobvite_company_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Company ID'),
    '#required' => TRUE,
    '#default_value' => variable_get('jobvite_company_id', ""),
    '#description' => t('Your company ID in Jobvite'),
  );

  $form['jobvite_infos']['jobvite_result_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of job requested'),
    '#default_value' => variable_get('jobvite_result_count', 100),
    '#required' => TRUE,
    '#element_validate' => array('element_validate_integer_positive'),
    '#description' => t('Number of jobs requested by query to the API.'),
  );

  $form['jobvite_infos']['jobvite_cron_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Time interval for jobvite'),
    '#default_value' => variable_get('jobvite_cron_interval', 3600),
    '#required' => TRUE,
    '#element_validate' => array('element_validate_integer_positive'),
    '#description' => t('Time in seconds between two importations. 3600 by default to launch the process every hour.'),
  );

  $form['jobvite_infos']['jobvite_json_feed_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Url of the job feed.'),
    '#required' => TRUE,
    '#default_value' => variable_get('jobvite_json_feed_url', "https://api.jobvite.com/v1/jobFeed"),
    '#description' => t('Enter url for the job feed of Jobvite.'),
  );

  $form['jobvite_infos']['jobvite_path_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix for the path of job page.'),
    '#description' => t('Presently, the path for individual job page is simply job/%jobvite_job. You could add a prefix of your choice for this path. Example: careers/'),
    '#default_value' => variable_get('jobvite_path_prefix', ""),
  );

  $form['jobvite_filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters on the query'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['jobvite_filters']['jobvite_job_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Job type'),
    '#default_value' => variable_get('jobvite_job_type', ""),
    '#description' => t('Job type you want recover. Let blank if you want all types.'),
  );

  $form['jobvite_filters']['jobvite_available_to'] = array(
    '#type' => 'select',
    '#title' => t('Available to'),
    '#options' => drupal_map_assoc(
      array(
        'External',
        'Internal',
      )
    ),
    '#default_value' => variable_get('jobvite_available_to', 'External'),
    '#description' => t('Publishing settings for your jobs. External by default.'),
  );

  $form['jobvite_filters']['jobvite_job_category'] = array(
    '#type' => 'textfield',
    '#title' => t('Category of job'),
    '#default_value' => variable_get('jobvite_job_category', ""),
    '#description' => t('Filter your request on a category of job. Let blank to recover jobs of all categories.'),
  );

  $form['jobvite_filters']['jobvite_job_department'] = array(
    '#type' => 'textfield',
    '#title' => t('Department'),
    '#default_value' => variable_get('jobvite_job_department', ""),
    '#description' => t('Filter your request on a specific department for jobs. Let blank to recover jobs of all department.'),
  );

  $form['jobvite_filters']['jobvite_job_location'] = array(
    '#type' => 'textfield',
    '#title' => t('Location for jobs'),
    '#default_value' => variable_get('jobvite_job_location', ""),
    '#description' => t('Location where you want recover jobs. Let blank if you want all locations.'),
  );

  $form['jobvite_filters']['jobvite_job_region'] = array(
    '#type' => 'textfield',
    '#title' => t('Region for jobs'),
    '#default_value' => variable_get('jobvite_job_region', ""),
    '#description' => t('Region where you want jobs are proposed. Let blank if you want all regions.'),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = "jobvite_admin_form_submit";
  return $form;
}

/**
 * Callback submit for jobvite_admin_form.
 *
 * Rebuild menu for the change of jobvite_path_prefix.
 */
function jobvite_admin_form_submit($form, &$form_state) {
  menu_rebuild();
}
