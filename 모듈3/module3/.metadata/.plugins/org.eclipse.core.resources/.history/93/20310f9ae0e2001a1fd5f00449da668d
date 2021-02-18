<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="ko">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>

    <script src="https://use.fontawesome.com/releases/v5.2.0/js/all.js"></script>
    <link rel="stylesheet" href="../../css/dinner41.css">

    <title>Map</title>
</head>

<body>
<!--네비게이션 바-->
<nav class="navbar navbar-light light_green">

    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>

    <!--사용자 위치-->
    <div class="btn-group">
        <input type="text" class="btn btn-outline-dark disable opacity -hover" value="" readonly>
        <!--
        <div class="dropdown-menu">
            <a class="dropdown-item" href="#">주소 변경하기</a>
            <div class="dropdown-divider"></div>
            <a class="dropdown-item" href="#">현재 위치 기준</a>
        </div>
		-->
    </div>

    <a href="${pageContext.request.contextPath}/gm/cart">
        <img src="${pageContext.request.contextPath}/resources/icons/shopping-bag-solid.svg" class="cart" alt="no picture">
    </a>
    <!--메뉴-->
    <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav mr-auto">
            <li class="nav-item">
                <a class="nav-link" href="#">내정보 보기</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="#">결제내역</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="${pageContext.request.contextPath}/ALL/1/qna">1:1 문의</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="#"> </a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="#"> </a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="#">로그아웃</a>
            </li>
        </ul>
    </div>
</nav>

<!--검색창-->
<div>
    <form class="form-inline">
        <div class="col-9" style="padding: 3pt;">
            <input class="form-control" type="search" placeholder="매장 입력" id="search_input" style=" width: 100%"/>
        </div>
        <div class="col-3" style="padding: 3pt 3pt 3pt 0;">
            <button class="btn btn-outline-success btn-block" type="submit" id="search_button">찾기</button>
        </div>
    </form>
</div>

<div>
    <div class="form-inline">
        <div class="col-9" style="padding: 3pt;">
            <div class="card card-body" style="height: 150pt">
                지도
            </div>
        </div>

        <div class="col-3" style="padding: 3pt 3pt 3pt 0;">
            <div class="accordion" id="accordionExample" style="position: absolute;top: -72pt; right: 3pt; width: 97%">

                <div class="card">
                    <div class="card-header" id="headingOne" style="background-color: #CFE3A1;">
                        <button class="btn btn-block text-center trim" type="button" data-toggle="collapse" data-target="#collapseOne" aria-expanded="true" aria-controls="collapseOne">
                            카테고리
                        </button>
                    </div>

                    <div id="collapseOne" class="collapse show" aria-labelledby="headingOne" data-parent="#accordionExample">
                        <div class="card-body trim">
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="all" value="ALL">전체</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="kor" value="KOR">한식</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="jap" value="JAP">일식</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="sna" value="SNA">분식</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="ric" value="RIC">떡</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="bre" value="BRE">제과</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="chi" value="CHI">치킨</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="piz" value="PIZ">피자</button></div>
                            <div class="text-center map_button"><button type="button" class="btn btn-default btn-block" name="category_button" id="etc" value="ETC">기타</button></div>
                        </div>
                    </div>
                </div>

<!-- 
                <div class="card">
                    <div class="card-header" id="headingTwo" style="background-color: #CFE3A1;">
                        <button class="btn btn-block text-center collapsed trim" type="button" data-toggle="collapse" data-target="#collapseTwo" aria-expanded="false" aria-controls="collapseTwo" >
                            제공유형
                        </button>
                    </div>
                    <div id="collapseTwo" class="collapse" aria-labelledby="headingTwo" data-parent="#accordionExample">
                        <div class="card-body trim">
                            <div class="text-center map_button">도시락</div>
                            <div class="text-center map_button">밀키트</div>
                            <div class="text-center map_button">완전조리식</div>
                        </div>
                    </div>
                </div>
 -->
            </div>
        </div>
    </div>
</div>

<div class="last_block"></div>
</body>
</html>