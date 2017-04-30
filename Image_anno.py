# fucntion for converting a array of strings to array of floats 
def stof(line):
	temp = []
	for x in xrange(0,len(line)-1):
		s=float(line[x])
		temp.append(s)
	return temp;	

# fuxntion for converting an array of strings to array of integers		
def ston(line):
	temp = []
	for x in xrange(0,len(line)):
		s=int(line[x])
		temp.append(s)
	return temp;	

# calcualting the euclidean distance between two vectors X, Y
def calc_Ed(X , Y):
	ED =0.00
	for x in xrange(0,len(Y)):
		ED += ((X[x]-Y[x])*(X[x]-Y[x]))
	return ED ;


# bubble sort
def sort(Ed,col):
	for x in xrange(0,len(Ed)):
		for y in xrange((x+1),len(Ed)):
			if Ed[x][col]>Ed[y][col]:
				Ed[x][0]=Ed[x][0]+Ed[y][0]
				Ed[y][0]=Ed[x][0]-Ed[y][0]
				Ed[x][0]=Ed[x][0]-Ed[y][0]

				Ed[x][1]=Ed[x][1]+Ed[y][1]
				Ed[y][1]=Ed[x][1]-Ed[y][1]
				Ed[x][1]=Ed[x][1]-Ed[y][1]

	return Ed;

# calculating the number of labels attached to image vector v as per the data_anno_test
def point(v):
	count = 0
	for x in xrange(0,len(v)):
		if(v[x]==1):
			count+=1
	return count;		

# extracting the floating valiues from the files (features file)
def extraxt_features(filename):
	data = []
	f=open(filename,'r')
	lins = f.read().splitlines()
	for x in xrange(0,len(lins)):
		data.append(stof(lins[x].split(' ')))
	return data;

# extracting the annotatons from the file 
def extraxt_anno(filename):
	data = []
	f=open(filename,'r')
	lins = f.read().splitlines()
	# line  = lins[0].split('   ')
	for x in xrange(0,len(lins)):
	 	data.append(ston(lins[x].split('   ')))
	return data;

def main(k):	
	data=[]
	data_test=[]
	# data {} set of the features on each image of training set 
	data = extraxt_features("training_data.txt")
	# data_test {} set of the features on each image of test set
	data_test = extraxt_features("test_data.txt")

	# print len(data[0])
	# print len(data_test[0])

	# data_anno {} is the list having the matrix 
	# defining the label for each image of the training set
	# as a string of 0/1 of length 260 --'1' if it belongs to the image '0' if not belog to the image 
	data_anno = extraxt_anno("training_anno.txt")
	# data_anno_test {} is the list having the matrix 
	# defining the label for each image of the testing set
	# as a string of 0/1 of length 260 --'1' if it belongs to the image '0' if not belog to the image 
	data_anno_test = extraxt_anno("test_anno.txt")

	# print len(data_anno[0])
	# print len(data_anno_test[0])

	# list as per label 260 X n matrix 

	label_set = []
	# label set is the array of set of images as per each label 
	temp = []	
	co_occur=[]
	x=0
	y=0
	while x < len(data_anno[0]):
		temp = []
		y=0
		while y < len(data_anno):
			if (data_anno[y][x]==1):
				temp.append(y)	
			y=y+1
		label_set.append(temp)	
		x=x+1
# co_occur mwtrix initialization
	for x in xrange(0,len(label_set)):
		temp=[]
		for y in xrange(0,len(label_set)):
			temp.append(0)
		co_occur.append(temp)	

	# print len(co_occur)
	# print len(co_occur[0])

	# co_occur Matrix 
	for itr_llist in xrange(0,len(label_set)):
		l1=itr_llist
		for itr_llist2 in xrange(0,len(label_set)):
			l2=itr_llist2

			#comapre image lists of  l1, l2
			if l1==l2:
				pass
			else :	
				count = 0; 
				for itr_img_l1 in xrange(0,len(label_set[l1])):
					for itr_img_l2 in xrange(0,len(label_set[l2])):
						if(label_set[l1][itr_img_l1] == label_set[l2][itr_img_l2]):
							count=count+1

				# fill in the matrix				
				co_occur[l1][l2]=float(count)/len(label_set[l1])

	# for x in xrange(0,len(co_occur)):
	# 	print co_occur[x][x]

	# for x in xrange(0,len(data)):
	# 	if len(data[x])!=511:
	# 		print len(data[x])

	minn = len(data)
	for x in xrange(0,259):
	 		if len(label_set[x])<minn:
	 			minn = len(label_set[x])	

	#K = minn
	K=k
	count=0
	F1=0
	avg_recall=0.0
	avg_precision=0.0
	for itr in xrange(0,len(data_test)):
		# let test imge -> data_test[itr]
		test_img_id= itr
		# test_label_set {} is the set of k images extracted from label_set per label 
		# of the form of array of image sets [I1,I2 ....] for each label 
		test_label_set = []
		for x in xrange(0,len(label_set)):
			# every label set select K top images matching 			
			ed_set = []
			# ed_set {} is the array of vector [distance,image_id] 
			# where distance is the distance of the image from the test_img 
			for itr_l in xrange(0,len(label_set[x])):				
				temp_edset=[]
				img_id = label_set[x][itr_l]
				temp_edset.append(img_id)
				temp_edset.append(calc_Ed(data[img_id],data_test[test_img_id]))
				ed_set.append(temp_edset)

			sort(ed_set,1)

			# select top k entires inn the ed list 
			temp_test_set = []
			itr_ed = 0
			while itr_ed <len(ed_set) :
				if(itr_ed>K):
					break; 
				temp_test_set.append(ed_set[itr_ed][0])	
				itr_ed+=1

			test_label_set.append(temp_test_set)

		# image sets per label selected :: now 	find labels

		itr_test=0
		maxx =0 
		maxx_feature = -1
		sum_list=[]

		while (itr_test < len(test_label_set)):
			# for measure we use L2 on gist
			summ=0
			temp_sum=[]
			for x in xrange(0,len(test_label_set[itr_test])):
				img_id=test_label_set[itr_test][x]
				summ+=calc_Ed(data[img_id],data_test[test_img_id])
			summ=summ/len(test_label_set[itr_test])	
			temp_sum.append(summ)
			temp_sum.append(itr_test)
			sum_list.append(temp_sum)
			itr_test+=1		
		
		# exract top label of the list 

		# sum_list is the list of the weights of the labels
		# with weights in form of array of vectors of type ->[w,label]
		sort (sum_list,0)
		top_label_itr=0
		top_label=sum_list[top_label_itr][1]
		temp_tst_label_list=[]
		temp_tst_label_list.append(top_label)
		
		# extract K-1 labels using co-occur matrix 
		itr_test_label=0
		while itr_test_label <= (K-1):
			l1_co_occur=temp_tst_label_list[len(temp_tst_label_list)-1]
			maxx_prob=0.0
			maxx_prob_label=-1
			# find most probable label in the matrix 
			for x in xrange(0,len(co_occur[l1_co_occur])):
				if (maxx_prob<co_occur[l1_co_occur][x]):
					maxx_prob=co_occur[l1_co_occur][x]
					maxx_prob_label=x

			if maxx_prob_label!=-1:
				itr_test_label+=1
				temp_tst_label_list.append(maxx_prob_label)		
			else :
				# if no other label is co-occuring use the second 
				# most top label in the sorted weights 
				# in the sub_list of the labels
				top_label_itr+=1
				temp_tst_label_list.append(sum_list[top_label_itr][1])	
				
		temp_count=0
		# temp_tst_label_list {} 
		# -------is the probable list of the labels predicted by the algorithm
		for m in xrange(0,len(temp_tst_label_list)):
			if data_anno_test[test_img_id][temp_tst_label_list[m]]==1:
				temp_count+=1
		# print temp_count
		m1=temp_count
		m2=K
		m3=point(data_anno_test[test_img_id])
		precision=float(m1)/m2
		recall=float(m1)/m3
		avg_precision+=precision
		avg_recall+=recall
		# # f1 score -- 2*temp_count/(K+(points_where_data_anno_test=1))
		# temp_f1 = float(2*temp_count)/(K+point(data_anno_test[test_img_id]))
		# print temp_f1
	avg_precision=avg_precision /len(data_test)
	avg_recall=avg_recall/len(data_test)	
	avg_precision*=100
	avg_recall*=100
	F1=2*(avg_precision*avg_recall)/(avg_precision+avg_recall)	
	print F1	

if __name__ == '__main__':
	main(4)	
