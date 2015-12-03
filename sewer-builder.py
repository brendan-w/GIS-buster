
import json
from affine import Affine



def main():
	with open("output-checked.json", "r") as f:
		data = json.loads(f.read())["nodes"]

		fwd = Affine.from_gdal(1396527.486, 1156707.409, 2431, 241, \
							   1402186.618, 1156770.797, 10592, 247, \
							   1396559.438, 1150970.182, 2396, 8909, \
							   1402226.101, 1151037.144, 10931, 8908)

		print(fwd)


if __name__ == "__main__":
	main()
