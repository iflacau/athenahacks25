import requests
from bs4 import BeautifulSoup
import json
import sys
import re
import urllib.parse

if __name__ == "__main__":
    full_url = sys.stdin.readline().strip()
    if not full_url:
        print(json.dumps({"error": "No URL provided"}), file=sys.stderr) # Return JSON error to stderr
        sys.exit(1)
    try:
        response = requests.get(full_url)
        response.raise_for_status()  # Raise HTTPError for bad responses
        soup = BeautifulSoup(response.content, 'html.parser')
        script = soup.find('script', text=re.compile('createFullCalendar'))
        

        if script:
            json_match = re.search(r'createFullCalendar\(\$.parseJSON\((.*?)\)\)', script.text, re.DOTALL)
            if json_match:
                json_data_str = json_match.group(1)[1:-1]
                calendar_data = json.loads(json_data_str)
                print(calendar_data)
                sys.exit(0)

            else:
                error_message = "JSON data not found in the script."
                print(json.dumps({"error": error_message}), file=sys.stderr) # Return JSON error to stderr
                sys.exit(1)
        else:
            error_message = "No relevant script found on the page."
            print(json.dumps({"error": error_message}), file=sys.stderr) # Return JSON error to stderr
            sys.exit(1)

    except requests.exceptions.RequestException as e:
        error_message = f"HTTP Request Error: {e}"
        print(json.dumps({"error": error_message}), file=sys.stderr) # Return JSON error to stderr
        sys.exit(1)
    except json.JSONDecodeError as e:
        error_message = f"JSON Decode Error: {e}"
        print(json.dumps({"error": error_message}), file=sys.stderr) # Return JSON error to stderr
        sys.exit(1)
    except ValueError as e:
        error_message = f"Value Error: {e}"
        print(json.dumps({"error": error_message}), file=sys.stderr) # Return JSON error to stderr
        sys.exit(1)
    except Exception as e:
        error_message = f"An unexpected error occurred: {e}"
        print(json.dumps({"error": error_message}), file=sys.stderr) # Return JSON error to stderr
        sys.exit(1)
    finally:
        sys.exit(0)