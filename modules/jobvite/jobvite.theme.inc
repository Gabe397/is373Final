<?php

/**
 * @file
 * Theme functions and (pre)process callbacks for the Jobvite module.
 */

/**
 * Prepare variables for the job template.
 *
 * @see jobvite.tpl.php
 */
function template_preprocess_jobvite_job(&$variables) {
  $job = $variables['job'];
  $location = explode(',', $job->location);

  if (count($location) == 3) {
    array_splice($location, 1, 1);
    $job->location = implode(',', $location);
  }

  $variables += jobvite_prepare_job_for_template($job);
}

/**
 * Prepare variables for the jobs template.
 *
 * @see jobvites.tpl.php
 */
function template_preprocess_jobvite_jobs_list(&$variables) {
  $variables['raw_jobs'] = $variables['jobs'];
  $variables['jobs'] = array_map('jobvite_prepare_job_for_template', $variables['jobs']);
}

/**
 * Prepare data for template.
 */
function jobvite_prepare_job_for_template($job) {
  $prepared_job = array();
  $apply_url = $job->applyUrl;

  $query = parse_url($apply_url, PHP_URL_QUERY);

  if ($query) {
    $apply_url .= '&nl=0';
  }
  else {
    $apply_url .= '?nl=0';
  }

  $prepared_job['id'] = $job->id;
  $prepared_job['title'] = $job->title;
  $prepared_job['location'] = $job->location;
  $prepared_job['city'] = $job->city;
  $prepared_job['country'] = $job->country;
  $prepared_job['state'] = $job->state;
  $prepared_job['region'] = $job->region;
  $prepared_job['department'] = $job->department;
  $prepared_job['detail_url'] = $job->detailUrl;
  $prepared_job['apply_url'] = $apply_url;
  $prepared_job['description'] = $job->description;
  $prepared_job['brief_description'] = $job->briefDescription;
  $prepared_job['path'] = jobvite_page_path($job);
  $prepared_job['classes_array'][] = "jobvite-" . drupal_html_class(filter_xss_admin($job->jobType));
  $prepared_job['classes_array'][] = "jobvite-" . drupal_html_class(filter_xss_admin($job->region));

  return $prepared_job;
}
